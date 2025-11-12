#pragma once
#include <iostream>
#include "matrix.h"

class Fibonacci final {

public:

    //рекурсивный алгоритм расчета чисел фибоначчи
    uint64_t static req_fibonacci(uint32_t n) {
        if (n < 2) return 1;        
        return req_fibonacci(n - 1) + req_fibonacci(n - 2);
    }

    //итеративный алгоритм расчета чисел фибоначчи
    uint64_t static iter_fibonacci(uint32_t n) {
        
        if (n < 3) return 1;        
        uint64_t f1 = 1;        
        uint64_t f2 = 1;
        
        for (uint32_t i = 2; i != n; ++i) {
            uint64_t temp = f2;
            f2 += f1;
            f1 = temp;            
        }       

        return f2;
    }


};