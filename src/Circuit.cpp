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

void Circuit::add_classic(size_t bits) {
    if(3 * bits + 1 > size)
        throw std::out_of_range("classical addition requires 3n + 1 bits to add_classic two n-bit numbers");
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

void Circuit::qft(size_t first, size_t last) {
    for(int i = 0; i < last - first; i++) {
        h(i + first);
        for(int k = 2; k + i <= last - first; k++) {
            Complex tmp = (1.0 / (1 << k));
            cp(2 * M_PI * tmp, first + i, first + k + i - 1);
        }
    }
}
void Circuit::iqft(size_t first, size_t last) {
    for(int i = (int)(last - first) - 1; i >= 0; i--) {
        for(int k = (int)(last - first) - i; k >= 2; k--) {
            Complex tmp = (1.0 / (1 << k));
            cp(-2 * M_PI * tmp, first + i, first + k + i - 1);
        }
        h(first + i);
    }
}

void Circuit::qft_approximate(size_t first, size_t last) {
    int threshold = (int)log2(last - first) + 1;
    for(int i = 0; i < last - first; i++) {
        h(first + i);
        for(int k = 2; k + i <= (last - first) && k <= threshold; k++) {
            Complex tmp = (1.0 / (1 << k));
            cp(2 * M_PI * tmp, first + i, first + k + i - 1);
        }
    }
}
void Circuit::iqft_approximate(size_t first, size_t last) {
    if(first >= last)
        throw std::invalid_argument("argument \"first\" must be less than \"last\"");
    if(last > size)
        throw std::out_of_range("range is bigger than system size");
    int threshold = (int)log2(last - first) + 1;
    for(int i = (int)(last - first) - 1; i >= 0; i--) {
        for(int k = std::min((int)(last - first) - i, threshold); k >= 2; k--) {
            Complex tmp = (1.0 / (1 << k));
            cp(-2 * M_PI * tmp, first + i, first + k + i - 1);
        }
        h(first + i);
    }
}
void Circuit::add_quantum(size_t bits) {
    if(2 * bits > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits; j++) {
            Complex tmp = (1.0 / (1 << (j + 1)));
            cp(2 * M_PI * tmp, j,  i + bits);
        }
    }
}
void Circuit::add_quantum_approximate(size_t bits) {
    if(2 * bits > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");
    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits; j++) {
            if(j > threshold)
                break;
            cp(j + 1, j,  i + bits);
        }
    }
}