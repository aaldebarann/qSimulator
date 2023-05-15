//
// Created by Алексей on 14.05.2023.
//

#ifndef QSIMULATOR_MATRIX_H
#define QSIMULATOR_MATRIX_H

#include <complex>
#include <vector>
using std::vector;

typedef std::complex<float> Complex;

// квадратная матрица
class Matrix {
    Complex* pMem;
    size_t sz; // size
public:
    size_t size() const {return sz;}

    Matrix(size_t size);
    ~Matrix();
    Matrix& operator=(const Matrix& m) {
        sz = m.size();
        delete[] pMem;
        pMem = new Complex[size()*size()];
        copy(m.pMem, m.pMem + size()*size(), pMem);
        return *this;
    }

    Complex& operator()(size_t row, size_t column);
    bool operator==(const Matrix&) const;
    Matrix& operator+=(Matrix& m);
    vector<Complex> operator*(const vector<Complex>& v);

    Matrix kron(Matrix& x); // computes the Kronecker product
};



#endif //QSIMULATOR_MATRIX_H
