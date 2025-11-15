#pragma once
#include <iostream>
#include "matrix.h"

//класс умеет возводить числа double в степень несколькими способами
class Pow {
public:	
	//функция итеративного возведения числа в степень	
	double static simple_pow(double base, uint64_t exp) {
		
		double result = 1; //присваиваем начальное значение - единицу (чтобы учесть возможное значение exp = 0)

		for (uint64_t iter = 0; iter != exp; ++iter) {
			result *= base;
		}

		return result;
	}
	
	//Функция возведения в степень через домножение
	double static quick_pow(double base, uint64_t exp) {
		
		if (0 == exp) return 1; //базовый случай

		double result = quick_pow(base, exp / 2);
		result *= result;

		if (exp % 2 == 1) {
			result *= base;
		}

		return result;
	}	

	//Функция возведения в степень через двоичное разложение показателя степени
	double static binary_pow(double base, uint64_t exp) {					
		
		double result = 1; //начальное значение

		// Находим позицию старшего бита
		uint64_t bit_pos = 0;
		uint64_t temp = exp;
		while (temp > 1) {
			temp >>= 1;
			bit_pos++;
		}

		// Обрабатываем биты от старшего к младшему
		for(int64_t i = bit_pos; i >= 0; i--) {
			result *= result;
			if (exp & (1ll << i)) {
				result *= base;
			}
		}
		return result;
	}
};