#pragma once
#include <iostream>
#include <functional>
#include <vector>

//класс умеет считать количество простых чисел в диапазоне от 0 до n
class Prime {
public:

#include <functional>
#include <cmath>

    // Разные реализации is_prime
    //перебор делитетелй
    bool static is_prime_naive(size_t num) {
        for (size_t i = 2; i < num; ++i) {
            if (num % i == 0) return false;
        }
        return num >= 2;
    }

    //перебор делителей до корня из num
    bool static is_prime_lim(size_t num) {
        
        size_t lim = static_cast<size_t>(std::sqrt(num));
        for (size_t i = 2; i <= lim; ++i) {
            if (num % i == 0) return false;
        }
        return num >= 2;
    }

    //перебор делителей до корня из num с пропуском четных
    bool static is_prime_optimized(size_t num) {
        if (num < 2) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;

        size_t lim = static_cast<size_t>(std::sqrt(num));
        for (size_t i = 3; i <= lim; i += 2) {
            if (num % i == 0) return false;
        }
        return true;
    }

    //перебор делителей до корня из num с делением только на простые числа (прыжки на 6 (6k - 1 / 6k + 1))
    bool static is_prime_6k(size_t num) {
        if (num < 2) return false;
        if (num == 2 || num == 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;

        size_t lim = static_cast<size_t>(std::sqrt(num));

        for (size_t i = 5; i <= lim; i += 6) {
            if (num % i == 0) return false;      // проверяем 6k-1
            if (num % (i + 2) == 0) return false; // проверяем 6k+1
        }
        return true;
    }

    // Общая функция подсчета простых чисел до n
    size_t static count_primes(size_t n, std::function<bool(size_t)> is_prime) {
        size_t count = 0;
        for (size_t i = 2; i <= n; ++i) {
            if (is_prime(i)) ++count;
        }
        return count;
    }

    //подсчет количества простых чисел через простое решето Эратосфена
    size_t static eratosphen(size_t n)  {
        std::vector<bool> sieve(n + 1, true);
        size_t count = 0;
        
        for (size_t i = 2; i <= n; ++i) {
            if (sieve[i]) { //если клеточка отмечена как простое число
                ++count; //считаем
                for (size_t j = i * i; j <= n; j += i) //и вычеркиваем
                    sieve[j] = false;
            }
        }
        return count;
    }

    //подсчет количества простых чисел через простое решето Эратосфена
    //c сохраниением данных в битовой маске
    size_t static eratosphen_bits_optimized(size_t n) {
        if (n < 2) return 0;
        
        size_t odd_count = (n + 1) / 2;  // количество нечетных чисел <= n
        size_t vector_size = odd_count / 32 + 1;
        std::vector<uint32_t> sieve(vector_size, 0);

        auto get_bit = [&](size_t num) -> bool {
            if (num % 2 == 0) return num == 2;  // четные - составные (правда мы их все-равно исключили)
            size_t index = (num - 1) / 2;  // преобразуем в индекс нечетных
            return (sieve[index / 32] & (1U << (index % 32))) != 0;
        };

        auto set_bit = [&](size_t num) {
            if (num % 2 == 1) {  // только нечетные
                size_t index = (num - 1) / 2;
                sieve[index / 32] |= (1U << (index % 32));
            }
        };

        size_t count = (n >= 2) ? 1 : 0;  // учитываем 2

        // Обрабатываем нечетные числа
        for (size_t i = 3; i <= n; i += 2) {
            if (!get_bit(i)) {
                ++count;
                // Вычёркиваем кратные, начиная с i*i
                for (size_t j = i * i; j <= n; j += 2 * i) {  // шаг 2i
                    set_bit(j);
                }
            }
        }

        return count;
    }

    //подсчет количества простых чисел через решето Эратосфена с линейным временем
    //(через формирование списка наименьших простых делителей)
    size_t static eratosphen_linear(size_t n) {
        if (n < 2) return 0;

        std::vector<size_t> lp(n + 1, 0);  // lp[i] - наименьший простой делитель i
        std::vector<size_t> pr;            // pr - список простых чисел

        for (size_t i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                // i - простое число
                lp[i] = i;
                pr.push_back(i);
            }

            // Для всех найденных простых чисел
            for (size_t j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= n; ++j) {
                lp[i * pr[j]] = pr[j];
            }
        }

        return pr.size();  // количество простых чисел
    }

};