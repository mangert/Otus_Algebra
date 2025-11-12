#pragma once
#include <iostream>
#include "matrix.h"

class Pow {

public:
	
	//функци€ итеративного возведени€ числа в степень	
	double static simple_pow(double base, uint32_t exp) {
		
		double result = 1; //присваиваем начальное значение - единицу (чтобы учесть возможное значение exp = 0)

		for (uint32_t iter = 0; iter != exp; ++iter) {
			result *= base;
		}

		return result;
	}
	
	//‘ункци€ возведени€ в степень через домножение
	double static quick_pow(double base, uint32_t exp) {
		
		if (0 == exp) return 1; //базовый случай

		double result = quick_pow(base, exp / 2);
		result *= result;

		if (exp % 2 == 1) {
			result *= base;
		}

		return result;
	}	

	//‘ункци€ возведени€ в степень через двоичное разложение показател€ степени
	double static binary_pow(double base, uint32_t exp) {					
		
		double result = 1; //начальное значение

		// Ќаходим позицию старшего бита
		int bit_pos = 0;
		uint32_t temp = exp;
		while (temp > 1) {
			temp >>= 1;
			bit_pos++;
		}

		// ќбрабатываем биты от старшего к младшему
		for (int i = bit_pos; i >= 0; i--) {
			result *= result;
			if (exp & (1 << i)) {
				result *= base;
			}
		}
		return result;
	}
};