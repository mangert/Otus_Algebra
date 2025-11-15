#pragma once
#include <iostream>
#include <functional>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <vector>

template<typename ResultType, typename... Args>
class Test {
public:
    using TestFunction = std::function<ResultType(Args...)>;

    Test(TestFunction run, const std::string& test_folder)
        : test_run(run), folder(test_folder) {
    }

    void run() {
        namespace fs = std::filesystem;

        int iter = 0;
        while (true) {
            std::string fileIn = getTestPath(iter, "in");
            std::string fileOut = getTestPath(iter, "out");

            if (!fs::exists(fileIn) || !fs::exists(fileOut)) break;

            std::vector<std::string> inputs = readFileLines(fileIn);
            std::string expected = readFile(fileOut);  // результат всегда одна строка

            _run(iter, inputs, expected);
            ++iter;
        }
    }

private:
    void _run(int testNum, const std::vector<std::string>& inputs, const std::string& expected) {
        
        // Форматируем аргументы для вывода
        std::string args_str;
        if (inputs.size() == 1) {
            args_str = "n=" + inputs[0];
        }
        else if (inputs.size() == 2) {
            args_str = "base=" + inputs[0] + ", exp=" + inputs[1];
        }

        auto start = std::chrono::high_resolution_clock::now();
        try {
            auto result = call_function(inputs);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            // Для всех типов - численное сравнение
            if constexpr (std::is_arithmetic_v<ResultType>) {
                ResultType result_val = result;
                ResultType expected_val = static_cast<ResultType>(parse_double(expected));                

                // Сравниваем с допуском для вещественных чисел
                double tolerance = 1e-10;
                bool is_equal;

                if constexpr (std::is_integral_v<ResultType>) {
                    is_equal = (result_val == expected_val);
                }
                else {
                    is_equal = (std::abs(result_val - expected_val) < tolerance * std::abs(expected_val));
                }

                if (is_equal) {
                    std::cout << "Тест " << testNum << " OK: " << args_str
                        << " результат: " << result_val
                        << " время: " << duration << "us\n";
                }
                else {
                    double diff = std::abs(static_cast<double>(result_val) - static_cast<double>(expected_val));
                    std::cout << "Тест " << testNum << " ОШИБКА: " << args_str
                        << " результат: " << result_val
                        << " ожидалось: " << expected_val
                        << " разница: " << std::scientific << diff << std::fixed
                        << " время: " << duration << "us\n";
                }
            }
            else {
                // Для не-числовых типов - строковое сравнение
                std::string result_str = convert_result(result);
                std::string args_str = "args: " + std::to_string(inputs.size());

                if (result_str == expected) {
                    std::cout << "Тест " << testNum << " OK: " << args_str
                        << " результат: " << result_str
                        << " время: " << duration << "us\n";
                }
                else {
                    std::cout << "Тест " << testNum << " ОШИБКА: " << args_str
                        << " результат: " << result_str
                        << " ожидалось: " << expected
                        << " время: " << duration << " us\n";
                }
            }
        }
        catch (const std::exception& e) {
            std::cout << "Тест " << testNum << " НЕ ВЫПОЛНЕН: " << args_str
                << " ошибка: " << e.what() << "\n";
        }
    }
    
    // Упрощенная версия для конкретных случаев (неуниверсальная)
    ResultType call_function(const std::vector<std::string>& inputs) {
        if constexpr (std::is_same_v<ResultType, uint64_t> && sizeof...(Args) == 1) {
            // Фибоначчи: uint64_t(uint32_t)
            uint32_t arg = static_cast<uint32_t>(std::stoul(inputs[0]));
            return test_run(arg);
        }
        else if constexpr (std::is_same_v<ResultType, double> && sizeof...(Args) == 2) {
            // Степень: double(double, uint64_t)  
            double arg1 = parse_double(inputs[0]);
            uint64_t arg2 = static_cast<uint64_t>(std::stoull(inputs[1]));            
            return test_run(arg1, arg2);
        }
        else if constexpr (std::is_same_v<ResultType, size_t> && sizeof...(Args) == 2) {
            // Простые числа: size_t(size_t, функция)
            size_t arg1 = static_cast<size_t>(std::stoull(inputs[0]));
            // Второй аргумент - функция, передаём как есть
            return test_run(arg1, std::get<1>(std::tuple<Args...>{}));
        }

        throw std::invalid_argument("Unsupported function signature");
    }    

    double parse_double(const std::string& str) {
        std::stringstream ss(str);
        double result;
        ss >> result;
        return result;
    }
    
    std::string convert_result(const ResultType& result) {
        if constexpr (std::is_same_v<ResultType, double>) {
            // Для double используем точку вместо запятой
            std::stringstream ss;
            ss << std::fixed << std::setprecision(12) << result;
            std::string str = ss.str();
            // Убираем лишние нули в конце
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            if (str.back() == '.') str.pop_back();
            return str;
        }
        else {
            return std::to_string(result);
        }
    }

    // Чтение одной строки (для файлов с результатом)
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open: " + filename);
        std::string content;
        std::getline(file, content);
        file.close();
        return content;
    }

    // Чтение всех строк (для входных файлов)
    std::vector<std::string> readFileLines(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open: " + filename);

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        file.close();
        return lines;
    }

    std::string getTestPath(int testNum, const std::string& extension) {
        return std::string(TEST_DIR) + "/" + folder + "/test." +
            std::to_string(testNum) + "." + extension;
    }

private:
    TestFunction test_run;
    std::string folder;
};