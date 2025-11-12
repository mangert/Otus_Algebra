#include <iostream>
#include "pow.cpp"
#include "fib.cpp"
#include "matrix.h"

// === Класс Tickets - умеет считать количество "счастливых билетов" ===
/*class Tickets {
public:
	//функция подсчета количества счастливых билетов
	uint_fast64_t tickets(size_t n) {

		constexpr size_t digits = 10; //10 цифр от 0 до 9		
		// определим, максимальную сумму и сколько вариантов суммы у нас есть - длину массива сумм		
		const size_t max_sum = n * 9;
		const size_t len = max_sum + 1;

		//частоты вхождения каждой суммы, индекс массива - сама сумма
		std::vector<uint_fast64_t> frequency(len, 0);

		//заполняем массив сумм "слоями"		
		frequency[0] = 1; //Базовый случай - для порядка n = 0;

		for (int layer = 0; layer != n; ++layer) {
			std::vector<uint_fast64_t> temp(len, 0); //временный массив для слоя

			for (int sum_idx = 0; sum_idx != len; ++sum_idx) {

				if (frequency[sum_idx] == 0) continue; //нули прибавлять не будем

				//граница вложенного цикла - ограничена суммой текущего индекса строки и максимальной цифрой
				const int max_digit = std::min(digits, len - sum_idx);
				//формируем новые значения - идем "от нуля к 9" и добавляем со сдвигом значение из предыдущего слоя
				for (int digit = 0; digit != max_digit; ++digit) {
					temp[sum_idx + digit] += frequency[sum_idx];
				}
			}

			frequency = std::move(temp); //заменяем результирующий массив дополненым слоем
		}

		// считаем результат - складываем частоты вхождения каждой суммы, возведенные в квадрат
		uint_fast64_t result = 0;
		for (auto& item : frequency) {
			result += item * item;
		}

		return result;
	}
};*/

/*// === Класс Test  ===
class Test {

public:
	Test(std::function<uint_fast64_t(size_t)> run) : test_run(run) {} // в конструкторе передаем тестируемую функцию

	//основная функция тестирования
	void run()
	{
		namespace fs = std::filesystem;

		int iter = 0;
		while (true)
		{
			std::string fileIn = getTestPath(iter, "in"); //файл с входными данные
			std::string fileOut = getTestPath(iter, "out"); //файл с выходными данные
			if (!fs::exists(fileIn) || !fs::exists(fileOut))
				break;

			//забираем данные из файлов
			std::string input = readFile(fileIn);
			std::string output = readFile(fileOut);

			//вызываем тестируемую функцию
			std::string x = std::to_string(test_run(std::stoi(input)));
			if (x == output) {
				std::cout << "Тест " << iter << " OK: " << x << "\n";
			}
			else {
				std::cout << "Тест " << iter << "  ошибка:  " << x << " ожидалось: " << output << "\n";
			}
			++iter;
		}
	}
private: //служебные функции

	//получение пути к файлу с тестами
	std::string getTestPath(int testNum, const std::string& extension) {
		std::string path = std::string(TEST_DIR) + "/test." +
			std::to_string(testNum) + "." + extension;

		return path;
	}

	//считываем содержание файла
	std::string readFile(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error("Cannot open file: " + filename);
		}
		std::string content;
		std::getline(file, content);
		file.close();
		return content;
	}

private:
	//функция для тестирования
	std::function<uint_fast64_t(size_t)> test_run;
};*/

// === main  ===
int main() {
	setlocale(LC_ALL, "Russian");

	//double_t x = Pow::_pow(1.0001, 10000);
	double_t x = Pow::binary_pow(1.0001, 10000);
	std::cout << x << std::endl;
	
	Matrix<int> matrix{ {1,2}, {3, 4}, {5,6} };

	
	matrix.print_m();

	auto f = Fibonacci::iter_fibonacci(1000000);

	std::cout << f;


	
	//Tickets solver;	//экземляр класса с решением задачи

	//создаем экземпляр класса тестов (функцию заворачиваем в лямбду, т.к. она не статическая)
	//Test test([&solver](size_t n) { return solver.tickets(n); });

	//test.run(); //запускаем тесты

	return 0;
}