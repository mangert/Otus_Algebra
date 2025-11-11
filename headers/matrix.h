#pragma once

template <typename T>
class Matrix final {
    
    static_assert(std::is_arithmetic_v<T>,
        "Matrix can only be instantiated with arithmetic types");

public:
    Matrix() = delete; //матрицу без размеров создать нельзя

    Matrix(int rows, int columns) : size_row(rows), size_col(columns) {
        matrix = new T* [size_row];
        for (int i = 0; i < size_row; ++i) {
            matrix[i] = new T[size_col]{}; //инициализация по умолчанию
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) : size_row(other.size_row), size_col(other.size_col) {
        matrix = new T* [size_row];
        for (int i = 0; i < size_row; ++i) {
            matrix[i] = new T[size_col];
            for (int j = 0; j < size_col; ++j) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    // Конструктор перемещения
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

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // Освобождаем старую память
            for (int i = 0; i < size_row; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;

            // Выделяем новую и копируем
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

    //Получаем содержание матрицы:
    // Методы для доступа к элементам
    T& operator()(int row, int col) { 
        return matrix[row][col]; 
    }
    const T& operator()(int row, int col) const {
        return matrix[row][col]; 
    }
    //размеры матрицы
    int rows() const { return size_row; }
    int cols() const { return size_col; }

    template<typename U>
    auto operator*(const Matrix<U>& other) const->Matrix<decltype(T{} * U{})> {
        if (size_col != other.rows()) {
            throw std::invalid_argument("Matrix dimensions don't match for multiplication");
        }

        using ResultType = decltype(T{} * U{});
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

private:
    int size_row;
    int size_col;
    T** matrix;
};