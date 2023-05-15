//
// Created by Алексей on 14.05.2023.
//

#ifndef QSIMULATOR_MATRIX_H
#define QSIMULATOR_MATRIX_H

#include "Vector.h"
using std::complex;

// квадратная матрица
class Matrix {
    complex<float>* pMem;
public:
    const size_t size;

    Matrix(size_t size);
    ~Matrix();

    complex<float>& operator()(size_t row, size_t column);

    Vector operator*(Vector& v);

    Matrix kron(Matrix& x); // computes the Kronecker product
};



#endif //QSIMULATOR_MATRIX_H
