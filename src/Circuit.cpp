//
// Created by aleksei on 04.06.23.
//

#include "Circuit.h"
#include "Gates.h"
#include <cmath>

Circuit::Circuit(size_t size): size(size) {

}

void Circuit::i(size_t target) {
    v.push_back(forSystem(I(), target, size));
} // Identity gate
void Circuit::x(size_t target) {
    v.push_back(forSystem(X(), target, size));
} // NOT gate (Pauli-X)
void Circuit::y(size_t target) {
    v.push_back(forSystem(Y(), target, size));
} // Pauli-Y
void Circuit::z(size_t target) {
    v.push_back(forSystem(Z(), target, size));
} // Pauli-Z
void Circuit::h(size_t target) {
    v.push_back(forSystem(H(), target, size));
} // Hadamar gate
void Circuit::p(Complex phaseShift, size_t target) {
    v.push_back(forSystem(P(phaseShift), target, size));
} // Phase shift
void Circuit::cnot(size_t control, size_t target) {
    v.push_back(CNOT(control, target, size));
} // Controled not
void Circuit::ccnot(size_t control1, size_t control2, size_t target) {
    v.push_back(CCNOT(control1, control2, target, size));
} // Toffoli gate
void Circuit::cp(Complex phi, size_t target1, size_t target2) {
    v.push_back(CPHASE(phi, target1, target2, size));
} // Controlled phase rotation

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

void Circuit::qtf() {
    for(int i = 0; i < size; i++) {
        h(i);
        for(int k = 2; k + i <= size; k++) {
            Complex tmp = (1.0 / (1 << k));
            cp(2 * M_PI * tmp, i, k + i - 1);
        }
    }
}
void Circuit::iqtf() {
    for(int i = (int)size - 1; i >= 0; i--) {
        for(int k = (int)size - i; k >= 2; k--) {
            Complex tmp = (1.0 / (1 << k));
            cp(-2 * M_PI * tmp, i, k + i - 1);
        }
        h(i);
    }
}

void Circuit::qtf_approximate() {
    int threshold = (int)log2(size) + 1;
    for(int i = 0; i < size; i++) {
        h(i);
        for(int k = 2; k + i <= size && k <= threshold; k++) {
            Complex tmp = (1.0 / (1 << k));
            cp(2 * M_PI * tmp, i, k + i - 1);
        }
    }
}
void Circuit::iqtf_approximate() {
    int threshold = (int)log2(size) + 1;
    for(int i = (int)size - 1; i >= 0; i--) {
        for(int k = std::min((int)size - i, threshold); k >= 2; k--) {
            Complex tmp = (1.0 / (1 << k));
            cp(-2 * M_PI * tmp, i, k + i - 1);
        }
        h(i);
    }
}
