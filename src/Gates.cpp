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
}
// functions return matrix for quantum gates in n-dimensional system
Matrix I(size_t target, size_t numberOfQubits) {
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");

    size_t size = (size_t)pow(2, (double )numberOfQubits);
    Matrix matrix{size, 0}; // zero matrix
    for(int i = 0; i < matrix.size(); i++) {
        matrix(i, i) = 1;
    }
    return matrix;
}
Matrix X(size_t target, size_t numberOfQubits) {
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");

    Matrix matrix{1, 1}; // matrix (1)
    Matrix x = X();
    Matrix id = I();
    for(int i = 0; i < numberOfQubits; i++) {
        if(i == target) {
            matrix = matrix.kron(x);
        } else {
            matrix = matrix.kron(id);
        }
    }
    return matrix;
}
Matrix Y(size_t target, size_t numberOfQubits) {
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");

    Matrix matrix{1, 1}; // matrix (1)
    Matrix y = Y();
    Matrix id = I();
    for(int i = 0; i < numberOfQubits; i++) {
        if(i == target) {
            matrix = matrix.kron(y);
        } else {
            matrix = matrix.kron(id);
        }
    }
    return matrix;
}
Matrix Z(size_t target, size_t numberOfQubits) {
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");

    Matrix matrix{1, 1}; // matrix (1)
    Matrix z = Z();
    Matrix id = I();
    for(int i = 0; i < numberOfQubits; i++) {
        if(i == target) {
            matrix = matrix.kron(z);
        } else {
            matrix = matrix.kron(id);
        }
    }
    return matrix;
}
Matrix H(size_t target, size_t numberOfQubits) {
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");

    Matrix matrix{1, 1}; // matrix (1)
    Matrix h = H();
    Matrix id = I();
    for(int i = 0; i < numberOfQubits; i++) {
        if(i == target) {
            matrix = matrix.kron(h);
        } else {
            matrix = matrix.kron(id);
        }
    }
    return matrix;
}
Matrix P(size_t target, Complex phi, size_t numberOfQubits) {
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");

    Matrix matrix{1, 1}; // matrix (1)
    Matrix p = P(phi);
    Matrix id = I();
    for(int i = 0; i < numberOfQubits; i++) {
        if(i == target) {
            matrix = matrix.kron(p);
        } else {
            matrix = matrix.kron(id);
        }
    }
    return matrix;
}
Matrix CNOT(size_t control, size_t target, size_t numberOfQubits) {
    if(control >= numberOfQubits)
        throw std::out_of_range("control qubit number is out of range");
    if(target >= numberOfQubits)
        throw std::out_of_range("target qubit number is out of range");
    if(control == target)
        throw std::invalid_argument("target and control can't be the same qubit");


    Matrix m1{2, 0}, m2{2, 0};
    m1(0, 0) = m2(1, 1) = 1;
    Matrix id = I();
    Matrix x = X();

    Matrix res1{1, 1};
    for(int k = (int)numberOfQubits - 1; k >= 0; k--) {
        if(k == control)
            res1 = res1.kron(m1);
        else
            res1 = res1.kron(id);
    }
    Matrix res2{1, 1};
    for(int k = (int)numberOfQubits - 1; k >= 0; k--) {
        if(k == control)
            res2 = res2.kron(m2);
        else if(k == target)
            res2 = res2.kron(x);
        else
            res2 = res2.kron(id);
    }
    res1 += res2;
    return res1;
}