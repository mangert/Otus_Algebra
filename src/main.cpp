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

	Test<double, double, uint64_t> test_iter(Pow::simple_pow, "3.Power");
	test_iter.run();
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

	//3. Тестирование функций количества простых чисел
	

	
	
	//Tickets solver;	//экземляр класса с решением задачи

	//создаем экземпляр класса тестов (функцию заворачиваем в лямбду, т.к. она не статическая)
	//Test test([&solver](size_t n) { return solver.tickets(n); });

	//test.run(); //запускаем тесты

	return 0;
}