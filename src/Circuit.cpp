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
