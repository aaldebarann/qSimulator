//
// Created by aleksei on 28.05.23.
//

#include "gates/SingleQubitGate.h"

Matrix gates::SingleQubitGate::getMatrix(size_t systemSize) {
    if(target >= systemSize)
        throw std::out_of_range("target qubit number is out of range");

    Matrix result{1, 1}; // result (1)
    Matrix m = matrix();
    Matrix id = I();
    for(int i = 0; i < systemSize; i++) {
        if(i == target) {
            result = result.kron(m);
        } else {
            result = result.kron(id);
        }
    }
    return result;
}

gates::SingleQubitGate::SingleQubitGate(size_t target) : target(target) {}
