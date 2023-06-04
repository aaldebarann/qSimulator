//
// Created by Алексей on 14.05.2023.
//

#include <cstring>
#include "../include/Matrix.h"

Matrix::Matrix(size_t size): sz(size) {
    pMem = new Complex[sz*sz];
}
Matrix::Matrix(): Matrix(0){}
Matrix::Matrix(size_t size, Complex fillValue): Matrix(size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            (*this)(i, j) = fillValue;
        }
    }
}
Matrix::~Matrix() {
    delete[] pMem;
}
Complex& Matrix::operator()(size_t row, size_t column) {
    return pMem[row * size() + column];
}
Matrix& Matrix::operator+=(Matrix &m) {
    if(size() != m.size())
        throw std::invalid_argument("Invalid addition: matrix sizes doesn't match");
    for(int i = 0; i < size(); i++) {
        for(int j = 0; j < size(); j++) {
            (*this)(i, j) += m(i, j);
        }
    }
    return *this;
}
vector<Complex> Matrix::operator* (const vector<Complex>& v) {
    if(size() != v.size())
        throw std::invalid_argument("Invalid multiplication: matrix size doesn't match vector size");
    vector<Complex> result(size(), 0);
    for(int i = 0; i < size(); i++) {
        for(int j = 0; j < size(); j++) {
            result[i] += v[j] * (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::kron(Matrix &x) {
    Matrix result(this->size() * x.size());
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result.size(); j++) {
            result(i, j) = (*this)(i / x.size(), j / x.size()) * x(i % x.size(), j % x.size());
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix &m) const {
    if(size() != m.size())
        return false;
    for(int i = 0; i < size()*size(); i++) {
        if(pMem[i] != m.pMem[i])
            return false;
    }
    return true;
}

Matrix &Matrix::operator=(const Matrix &m)  {
    sz = m.size();
    delete[] pMem;
    pMem = new Complex[size()*size()];
    copy(m.pMem, m.pMem + size()*size(), pMem);
    return *this;
}

Matrix::Matrix(const Matrix &m) {
    pMem = new Complex[m.size()*m.size()];
    sz = m.size();
    std::memcpy(pMem, m.pMem, sizeof(Complex)*m.size()*m.size());
}

Matrix::Matrix(Matrix &&m) {
    pMem = m.pMem;
    m.pMem = nullptr;
    sz = m.size();
}





