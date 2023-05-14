//
// Created by Алексей on 14.05.2023.
//

#include "../include/Matrix.h"

Matrix::Matrix(size_t sz): size(sz) {
    pMem = new complex<float>[size*size];
}
Matrix::~Matrix() {
    delete[] pMem;
}
complex<float>& Matrix::operator()(size_t row, size_t column) {
    return pMem[row * size + column];
}
Vector Matrix::operator* (Vector &v) {
    Vector result(size, 0);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            result[i] += v[j] * (*this)(i, j);
        }
    }
    return result;
}
