//
// Created by aleksei on 27.05.23.
//
#include "Gates.h"

// functions return matrix for quantum gates
Matrix I() {
    Matrix matrix(2);
    matrix(0, 0) = matrix(1, 1) = 1;
    matrix(0, 1) = matrix(1, 0) = 0;
    return matrix;
} // Identity gate
Matrix X() {
    Matrix matrix(2);
    matrix(0, 0) = matrix(1, 1) = 0;
    matrix(0, 1) = matrix(1, 0) = 1;
    return matrix;
} // NOT gate or Pauli-X
Matrix Y() {
    Matrix matrix(2);
    matrix(0, 0) = matrix(1, 1) = 0;
    Complex i(0, 1);
    matrix(0, 1) = -i;
    matrix(1, 0) = i;
    return matrix;
} // Pauli-Y
Matrix Z() {
    Matrix matrix(2);
    matrix(0, 0) = 1;
    matrix(0, 1) = matrix(1, 0) = 0;
    matrix(1, 1) = -1;
    return matrix;
} // Pauli-Z
Matrix H() {
    Matrix matrix(2);
    double tmp = 1.0 / sqrt(2);
    matrix(0, 0) =  matrix(0, 1) = matrix(1, 0) = tmp;
    matrix(1, 1) = -tmp;
    return matrix;
} // Hadamard
Matrix P(Complex phi) {
    Matrix matrix(2);
    Complex i(0, 1);
    matrix(0, 0) = 1;
    matrix(0, 1) = matrix(1, 0) = 0;
    matrix(1, 1) = std::exp(phi * i);
    return matrix;
} // Phase shift
Matrix* CNOT(size_t control, size_t target, size_t systemSize) {
    if(control >= systemSize)
        throw std::out_of_range("control qubit number is out of range");
    if(target >= systemSize)
        throw std::out_of_range("target qubit number is out of range");
    if(control == target)
        throw std::invalid_argument("target and control can't be the same qubit");


    Matrix m1{2, 0}, m2{2, 0};
    m1(0, 0) = m2(1, 1) = 1;
    Matrix id = I();
    Matrix x = X();

    Matrix* res1 = new Matrix{1, 1};
    for(int k = (int)systemSize - 1; k >= 0; k--) {
        if(k == control)
            res1->kron(m1);
        else
            res1->kron(id);
    }
    Matrix* res2 = new Matrix{1, 1};
    for(int k = (int)systemSize - 1; k >= 0; k--) {
        if(k == control)
            res2->kron(m2);
        else if(k == target)
            res2->kron(x);
        else
            res2->kron(id);
    }
    (*res1) += (*res2);
    return res1;
} // Controlled not
Matrix* CCNOT(size_t control1, size_t control2, size_t target, size_t systemSize) {
    if(control1 >= systemSize || control2 >= systemSize)
        throw std::out_of_range("control qubit number is out of range");
    if(target >= systemSize)
        throw std::out_of_range("target qubit number is out of range");
    if(control1 == target || control2 == target || control1 == control2)
        throw std::invalid_argument("arguments must be different");


    Matrix m1{2, 0}, m0{2, 0};
    m1(1, 1) = m0(0, 0) = 1;
    Matrix id = I();
    Matrix x = X();

    Matrix* res1 = new Matrix{1, 1};
    for(int k = (int)systemSize - 1; k >= 0; k--) {
        if(k == control1)
            res1->kron(m1);
        else if(k == control2)
            res1->kron(m1);
        else if(k == target)
            res1->kron(x);
        else
            res1->kron(id);
    }
    Matrix* res2 = new Matrix{1, 1};
    for(int k = (int)systemSize - 1; k >= 0; k--) {
        if(k == control1)
            res2->kron(m0);
        else if(k == control2)
            res2->kron(m1);
        else if(k == target)
            res2->kron(id);
        else
            res2->kron(id);
    }
    Matrix* res3 = new Matrix{1, 1};
    for(int k = (int)systemSize - 1; k >= 0; k--) {
        if(k == control1)
            res3->kron(m1);
        else if(k == control2)
            res3->kron(m0);
        else if(k == target)
            res3->kron(id);
        else
            res3->kron(id);
    }
    Matrix* res4 = new Matrix{1, 1};
    for(int k = (int)systemSize - 1; k >= 0; k--) {
        if(k == control1)
            res4->kron(m0);
        else if(k == control2)
            res4->kron(m0);
        else if(k == target)
            res4->kron(id);
        else
            res4->kron(id);
    }
    *res1 += *res2 += *res3 += *res4;
    return res1;
} // Toffoli gate
Matrix* CPHASE(Complex phi, size_t target1, size_t target2, size_t systemSize) {
    // TODO: �������� �������� �� ������������ ����������
    size_t matrixSize = pow(2, systemSize);
    Matrix* result = new Matrix(matrixSize, 0);
    int mask = (1 << target1) + (1 << target2);

    Complex i(0, 1);
    for(int j = 0; j < matrixSize; j++) {
        if((j & mask) == mask) {
            (*result)(j, j) = std::exp(phi * i);
        } else {
            (*result)(j, j) = 1;
        }
    }
    return result;
} // Controlled phase rotation
Matrix* CCP(double phi, size_t control1, size_t control2, size_t target, size_t systemSize) {
    // TODO: �������� �������� �� ������������ ����������
    size_t matrixSize = pow(2, systemSize);
    Matrix* result = new Matrix(matrixSize, 0);
    int mask = (1 << control1) + (1 << control2) + (1 << target);

    Complex tmp(0, 1);
    tmp *= phi;
    for (int j = 0; j < matrixSize; j++) {
        if ((j & mask) == mask) {
            (*result)(j, j) = std::exp(tmp);
        }
        else {
            (*result)(j, j) = 1;
        }
    }
    return result;
}
Matrix* CCCP(double phi, size_t control1, size_t control2, size_t control3, size_t target, size_t systemSize) {
    // TODO: �������� �������� �� ������������ ����������
    size_t matrixSize = pow(2, systemSize);
    Matrix* result = new Matrix(matrixSize, 0);
    int mask = (1 << control1) + (1 << control2) + (1 << control3) + (1 << target);

    Complex tmp(0, 1);
    tmp *= phi;
    for (int j = 0; j < matrixSize; j++) {
        if ((j & mask) == mask) {
            (*result)(j, j) = std::exp(tmp);
        }
        else {
            (*result)(j, j) = 1;
        }
    }
    return result;
}
Matrix* CSWAP(size_t control, size_t target1, size_t target2, size_t systemSize) {
    size_t matrixSize = 1 << systemSize;
    Matrix* result = new Matrix(matrixSize, 0);
    int cmask = (1 << control);
    int t1mask = (1 << target1);
    int t2mask = (1 << target2);
    for(int i = 0; i < matrixSize; i++) {
        if((i & cmask) == 1 &&
                ((i & t1mask) > 0) != ((i & t2mask) > 0) ) {
            int k = (i ^ t1mask) ^ t2mask;
            (*result)(k, i) = 1;
            (*result)(i, k) = 1;
        } else {
            (*result)(i, i) = 1;
        }
    }
    return result;
}
// convert matrix of single-qubit gate to matrix for n-dimensional system
Matrix* forSystem(Matrix singleQubitMatrix, size_t target, size_t systemSize) {
    if(target >= systemSize) {
        throw std::out_of_range("Target qubit number is out of range");
    }
    Matrix* result = new Matrix{1, 1}; // result = (1)
    Matrix id = I();
    for(int i = (int)systemSize - 1; i >= 0; i--) {
        if(i == target) {
            result->kron(singleQubitMatrix);
        } else {
            result->kron(id);
        }
    }
    return result;
}
