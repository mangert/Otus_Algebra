#pragma once
#include <iostream>

template <typename T>
class Matrix final {
    
    static_assert(std::is_arithmetic_v<T>,
        "Matrix can only be instantiated with arithmetic types");

public:
    Matrix() = delete; //матрицу без размеров создать нельз€


    Matrix(int rows, int columns) : size_row(rows), size_col(columns) {
        matrix = new T* [size_row];
        for (int i = 0; i < size_row; ++i) {
            matrix[i] = new T[size_col]{}; //инициализаци€ по умолчанию
        }
    }

    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        size_row = init.size();
        if (size_row == 0) throw std::invalid_argument("Empty matrix");

        size_col = init.begin()->size();
        if (size_col == 0) throw std::invalid_argument("Empty rows");

        // ѕроверка размеров
        for (const auto& row : init) {
            if (row.size() != size_col) {
                throw std::invalid_argument("Inconsistent row sizes");
            }
        }

        // ¬ыделение пам€ти
        matrix = new T * [size_row];
        auto it = init.begin();
        for (int i = 0; i < size_row; ++i, ++it) {
            matrix[i] = new T[size_col];
            auto row_it = it->begin();
            for (int j = 0; j < size_col; ++j, ++row_it) {
                matrix[i][j] = *row_it;
            }
        }
    }

    //  онструктор копировани€
    Matrix(const Matrix& other) : size_row(other.size_row), size_col(other.size_col) {
        matrix = new T* [size_row];
        for (int i = 0; i < size_row; ++i) {
            matrix[i] = new T[size_col];
            for (int j = 0; j < size_col; ++j) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    //  онструктор перемещени€
    Matrix(Matrix&& other) noexcept
        : size_row(other.size_row), size_col(other.size_col), matrix(other.matrix) {
        other.matrix = nullptr;
        other.size_row = 0;  
        other.size_col = 0;
    }

    ~Matrix() {
        if (matrix) {
            for (int i = 0; i < size_row; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }

    // ќператор присваивани€
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // ќсвобождаем старую пам€ть
            for (int i = 0; i < size_row; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;

            // ¬ыдел€ем новую и копируем
            size_row = other.size_row;
            size_col = other.size_col;
            matrix = new T * [size_row];
            for (int i = 0; i < size_row; ++i) {
                matrix[i] = new T[size_col];
                for (int j = 0; j < size_col; ++j) {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
        }
        return *this;
    }

    //ѕолучаем содержание матрицы:
    // ћетоды дл€ доступа к элементам
    T& operator()(int row, int col) { 
        return matrix[row][col]; 
    }
    const T& operator()(int row, int col) const {
        return matrix[row][col]; 
    }
    //размеры матрицы
    int rows() const { return size_row; }
    int cols() const { return size_col; }

    //операции с матрицами
    //перемножение матриц
    template<typename U>
    auto operator*(const Matrix<U>& other) const->Matrix<decltype(T{} * U{})> {
        if (size_col != other.rows()) { //провер€ем, что матрицы могут быть перемножены
            throw std::invalid_argument("Matrix dimensions don't match for multiplication");
        }

        using ResultType = decltype(T{} * U{}); //тип элементов новой матрицы
        
        Matrix<ResultType> result(size_row, other.cols());

        for (int i = 0; i < size_row; ++i) {
            for (int j = 0; j < other.cols(); ++j) {
                for (int k = 0; k < size_col; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    };

    //только дл€ одинаковых типов шаблона (не можем мен€ть шаблонный тип дл€ this)
    Matrix<T>& operator*=(const Matrix<T>& other) {

        *this = (*this) * other;
        return *this;
    }

    //возведение в степень
    Matrix<T> pow(uint32_t exp) const {
        
        if (size_col != size_row) { //провер€ем, что матрица квадратна€
            throw std::invalid_argument("Matrix must be square for exponentiation");
        }
        if (exp == 0) {
            return Matrix<T>::identity(size_row);
        } 

        Matrix<T> result = Matrix<T>::identity(size_row);
        Matrix<T> temp = *this;

        while (exp > 0) {
            if (exp & 1) {
                result *= temp;
            }
            temp *= temp;
            exp >>= 1;
        }        
        
        return result;
    }

    //вспомогательный метод вывода матрицы
    void print_m() const {
        
        for (int row = 0; row < size_row; ++row) {
            for (int col = 0; col < size_col; ++col) {
                std::cout << matrix[row][col] << " ";
                
            }
        std::cout << "\n";
        }
    };
private:
    
    static Matrix<T> identity(int size) {
        Matrix<T> result(size, size);
        for (int i = 0; i < size; ++i) {
            result(i, i) = T{ 1 };
        }
        return result;       
    };

private:
    int size_row;
    int size_col;
    T** matrix;
};