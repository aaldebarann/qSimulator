//
// Created by aleksei on 04.06.23.
//

#include "Circuit.h"
#include "Gates.h"

Circuit::Circuit(size_t size): size(size) {

}

void Circuit::i(size_t target) {
    Matrix* id = new Matrix(I());
    Matrix* m = new Matrix(forSystem(*id, target, size));
    v.push_back(*m);
    delete m;
    delete id;
}
void Circuit::x(size_t target) {
    v.push_back(forSystem(X(), target, size));
}

void Circuit::y(size_t target) {
    v.push_back(forSystem(Y(), target, size));
}

void Circuit::z(size_t target) {
    v.push_back(forSystem(Z(), target, size));
}

void Circuit::h(size_t target) {
    v.push_back(forSystem(H(), target, size));
}

void Circuit::p(Complex phaseShift, size_t target) {
    v.push_back(forSystem(P(phaseShift), target, size));
}

void Circuit::cnot(size_t control, size_t target) {
    v.push_back(CNOT(control, target, size));
}

void Circuit::ccnot(size_t control1, size_t control2, size_t target) {
    v.push_back(CCNOT(control1, control2, target, size));
}

void Circuit::add(size_t bits) {
    if(3 * bits > size)
        throw std::out_of_range("classical addition requires 3n bits to add two n-bit numbers");
    for(int i = 0; i < bits; i++) {
        int tmp = i * 3;
        // carry gate
        ccnot(tmp+1, tmp+2, tmp+3);
        cnot(tmp+1, tmp+2);
        ccnot(tmp, tmp+2, tmp+3);
    }
    cnot(3*bits - 3, 3*bits - 2);
    // sum gate
    cnot(3*bits - 3, 3*bits - 2);
    cnot(3*bits - 4, 3*bits - 2);

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
