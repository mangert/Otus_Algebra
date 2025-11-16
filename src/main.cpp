#include <iostream>
#include "pow.cpp"
#include "fib.cpp"
#include "matrix.h"
#include "primes.cpp"
#include "test.h"

// === main  ===
int main() {
	setlocale(LC_ALL, "Russian");	
	
	//1. Тестирование функций возведения в степень	
	std::cout << "\n1. Возведение в степень" << "\n";
	std::cout << "* 1.a. Итеративное возведение в степень: Pow::simple_pow" << "\n";

	Test<double, double, uint64_t> test_iter_p(Pow::simple_pow, "3.Power");
	test_iter_p.run();
	std::cout << "\n-------------------------------------------------\n";
	
	std::cout << "* 1.b. Возведение в степень через домножение: Pow::quick_pow" << "\n";
	
	Test<double, double, uint64_t> test_quick(Pow::quick_pow, "3.Power");
	test_quick.run();
	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 1.c. Возведение в степень через двоичное разложение показателя: Pow::binary_pow" << "\n";

	Test<double, double, uint64_t> test_bin(Pow::binary_pow, "3.Power");
	test_bin.run();
	std::cout << "\n*************************************************\n";

	//2. Тестирование функций получения чисел фибоначчи
	
	std::cout << "\n2. Числа Фибоначчи" << "\n";
	std::cout << "* 2.a. Рекурсивный алгоритм расчета: Fibonacci::req_fibonacci" << "\n";
	
	Test<uint64_t, uint32_t> test_req(Fibonacci::req_fibonacci, "4.Fib");
	test_req.run();
	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 2.b. Итеративный алгоритм расчета: Fibonacci::iter_fibonacci" << "\n";

	Test<uint64_t, uint32_t> test_iter_f(Fibonacci::iter_fibonacci, "4.Fib");
	test_iter_f.run();
	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 2.с. Алгоритм расчета через матрицы: Fibonacci::matrix_fibonacci" << "\n";

	Test<uint64_t, uint32_t> test_matrix(Fibonacci::matrix_fibonacci, "4.Fib");
	test_matrix.run();
	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 2.d. Алгоритм расчета по формуле золотого сечения: Fibonacci::gold_fibonacci" << "\n";

	Test<uint64_t, uint32_t> test_gold(Fibonacci::matrix_fibonacci, "4.Fib");
	test_gold.run();
	std::cout << "\n*************************************************\n";

	//3. Тестирование функций количества простых чисел
	std::cout << "\n3. Поиск количества простых чисел" << "\n";
	std::cout << "* 3.a. Поиск простых чисел полным перебором делитетелeй: Prime::count_primes(Prime::is_prime_naive)" << "\n";
	
	auto prime_naive = [](size_t n) { return Prime::count_primes(n, Prime::is_prime_naive); };	
	Test<size_t, size_t> test_pr_n(prime_naive, "5.Primes");
	test_pr_n.run();

	std::cout << "\n-------------------------------------------------\n";	

	std::cout << "* 3.b. Поиск простых чисел перебором делителeй до корня из n: Prime::count_primes(Prime::is_prime_lim)" << "\n";

	auto prime_lim = [](size_t n) { return Prime::count_primes(n, Prime::is_prime_lim); };
	Test<size_t, size_t> test_pr_l(prime_lim, "5.Primes");
	test_pr_l.run();

	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 3.c. Поиск простых чисел перебором четных делителeй до корня из n: Prime::count_primes(Prime::is_prime_optimized)" << "\n";

	auto prime_opt = [](size_t n) { return Prime::count_primes(n, Prime::is_prime_optimized); };
	Test<size_t, size_t> test_pr_opt(prime_opt, "5.Primes");
	test_pr_opt.run();

	std::cout << "\n-------------------------------------------------\n";
	
	std::cout << "* 3.d. Поиск простых чисел перебором простых делителeй до корня из n: Prime::count_primes(Prime::is_prime_6k)" << "\n";

	auto prime_6k = [](size_t n) { return Prime::count_primes(n, Prime::is_prime_6k); };
	Test<size_t, size_t> test_pr_6k(prime_6k, "5.Primes");
	test_pr_6k.run();

	std::cout << "\n-------------------------------------------------\n";
	
	std::cout << "* 3.e. Поиск простых чисел через решето Эратосфена: Prime::eratosphen" << "\n";
	
	Test<size_t, size_t> test_pr_e(Prime::eratosphen, "5.Primes");
	test_pr_e.run();

	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 3.f. Поиск простых чисел через решето Эратосфена с линейным временем: Prime::eratosphen_linear" << "\n";

	Test<size_t, size_t> test_pr_el(Prime::eratosphen_linear, "5.Primes");
	test_pr_el.run();

	std::cout << "\n-------------------------------------------------\n";

	std::cout << "* 3.g. Поиск простых чисел через решето Эратосфена c сохранением в битовой маске: Prime::eratosphen_linear" << "\n";

	Test<size_t, size_t> test_pr_bit(Prime::eratosphen_bits_optimized, "5.Primes");
	test_pr_el.run();

	std::cout << "\n-------------------------------------------------\n";
	

	return 0;
}