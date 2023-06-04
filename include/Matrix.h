//
// Created by Алексей on 14.05.2023.
//

#ifndef QSIMULATOR_MATRIX_H
#define QSIMULATOR_MATRIX_H

#include <complex>
#include <vector>
using std::vector;

typedef std::complex<double> Complex;

// квадратная матрица
class Matrix {
    Complex* pMem;
    size_t sz; // size
public:
    size_t size() const {return sz;}

    Matrix();
    Matrix(size_t size);
    Matrix(size_t size, Complex fillValue);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m);
    ~Matrix();
    Matrix& operator=(const Matrix& m);

    Complex& operator()(size_t row, size_t column);
    bool operator==(const Matrix&) const;
    Matrix& operator+=(Matrix& m);
    vector<Complex> operator*(const vector<Complex>& v);

    Matrix kron(Matrix& x); // computes the Kronecker product
};



#endif //QSIMULATOR_MATRIX_H
