//
// Created by aleksei on 04.06.23.
//

#include "Circuit.h"
#include "Gates.h"

Circuit::Circuit(size_t size): size(size) {
    matrix = new Matrix((size_t)pow(2, size), 0);
    for(int i = 0; i < matrix->size(); i++) {
        (*matrix)(i, i) = 1;
    }
}

void Circuit::i(size_t target) {
    (*matrix) = forSystem(I(), target, size) * (*matrix);
}
void Circuit::x(size_t target) {
    (*matrix) = forSystem(X(), target, size) * (*matrix);
}
void Circuit::y(size_t target) {
    (*matrix) = forSystem(Y(), target, size) * (*matrix);
}
void Circuit::z(size_t target) {
    (*matrix) = forSystem(Z(), target, size) * (*matrix);
}
void Circuit::h(size_t target) {
    (*matrix) = forSystem(H(), target, size) * (*matrix);
}
void Circuit::p(Complex phaseShift, size_t target) {
    (*matrix) = forSystem(P(phaseShift), target, size) * (*matrix);
}
void Circuit::cnot(size_t control, size_t target) {
    (*matrix) = CNOT(control, target, size) * (*matrix);
}
void Circuit::ccnot(size_t control1, size_t control2, size_t target) {
    (*matrix) = CCNOT(control1, control2, target, size) * (*matrix);
}

void Circuit::add(size_t bits) {
    if(3 * bits + 1 > size)
        throw std::out_of_range("classical addition requires 3n + 1 bits to add two n-bit numbers");
    for(int i = 0; i < bits; i++) {
        int tmp = i * 3;
        // carry gate
        ccnot(tmp+1, tmp+2, tmp+3);
        cnot(tmp+1, tmp+2);
        ccnot(tmp, tmp+2, tmp+3);
    }
    cnot(3*bits - 2, 3*bits - 1);
    // sum gate
    cnot(3*bits - 2, 3*bits - 1);
    cnot(3*bits - 3, 3*bits - 1);

    for(int i = 1; i < bits; i++) {
        int tmp = ((int)bits - i - 1) * 3;
        // reverse carry gate
        ccnot(tmp, tmp + 2, tmp + 3);
        cnot(tmp + 1, tmp + 2);
        ccnot(tmp + 1, tmp + 2, tmp + 3);
        // sum gate
        cnot(tmp + 1, tmp + 2);
        cnot(tmp, tmp + 2);
    }
}
