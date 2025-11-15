#pragma once
#include <iostream>
#include "matrix.h"


//класс умеет рассчитывать n-е число фибоначчи несколькими способами
class Fibonacci final {
public:    
    //рекурсивный алгоритм расчета чисел фибоначчи
    uint64_t static req_fibonacci(uint32_t n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;
        //проверяем границу n
        if (n > MAX_N) {
            throw std::overflow_error("n is too large");
        }
        return req_fibonacci(n - 1) + req_fibonacci(n - 2);
    }

    //итеративный алгоритм расчета чисел фибоначчи
    uint64_t static iter_fibonacci(uint32_t n) {
        
        if (n == 0) return 0;
        
        //проверяем границу n
        if (n > MAX_N) {
            throw std::overflow_error("n is too large");
        }
        uint64_t prev = 1;
        uint64_t current = 1;
        
        for (uint32_t i = 2; i < n; ++i) {
            uint64_t next = prev + current;
            prev = current;
            current = next;            
        }
        return current;
    }
    
    //расчет чисел фибоначчи по формуле золотого сечения
    uint64_t static gold_fibonacci(uint32_t n) {
       
        //проверяем границу n
        if (n > MAX_N) {
            throw std::overflow_error("n is too large");                        
        }

        long double result = std::pow(FI, n) * INV_SQRT5 + 0.5L;
        
        return static_cast<uint64_t>(std::floor(result));
    }
    
    //расчет чисел фибоначчи через матрицу
    uint64_t static matrix_fibonacci(uint32_t n) {
        
        if (n == 0) return 0;

        //проверяем границу n
        if (n > MAX_N) {
            throw std::overflow_error("n is too large");
        }

        Matrix<uint64_t> init{ { 1, 1 }, { 1, 0} }; //базовый случай

        Matrix<uint64_t> res = init.pow(n - 1);
        
        return res(0, 0);
    }

private: 
    // Математические константы с высокой точностью
    static constexpr long double FI = 1.61803398874989484820458683436563811772030917980576L;
    static constexpr long double SQRT5 = 2.23606797749978969640917366873127623544061835961153L;
    static constexpr long double INV_SQRT5 = 0.4472135954999579392818347337462552470881236719223L;
    
    //Лимит переполнения типа -  максимальное n где F(n) ≤ 2⁶⁴-1, если n - uint64
    static constexpr uint32_t MAX_N = 93;
};