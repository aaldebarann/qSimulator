//
// Created by aleksei on 04.06.23.
//

#include "Circuit.h"
#include "Gates.h"
#include <cmath>
#include <iostream>
#include <corecrt_math_defines.h>

Circuit::Circuit(size_t size): size(size) {

}
Circuit::~Circuit() {
    for (Matrix* m: matrices) {
        delete m;
    }
}
// Basic gates
void Circuit::i(size_t target) {
    matrices.push_back(forSystem(I(), target, size));
    gates.push_back("I(" + std::to_string(target) + ")");
} // Identity gate
void Circuit::x(size_t target) {
    matrices.push_back(forSystem(X(), target, size));
    // gates.push_back("X(" + std::to_string(target) + ")");
} // NOT gate (Pauli-X)
void Circuit::y(size_t target) {
    matrices.push_back(forSystem(Y(), target, size));
    gates.push_back("Y(" + std::to_string(target) + ")");
} // Pauli-Y
void Circuit::z(size_t target) {
    matrices.push_back(forSystem(Z(), target, size));
    gates.push_back("Z(" + std::to_string(target) + ")");
} // Pauli-Z
void Circuit::h(size_t target) {
    matrices.push_back(forSystem(H(), target, size));
    gates.push_back("H(" + std::to_string(target) + ")");
} // Hadamar gate
void Circuit::p(double phaseShift, size_t target) {
    matrices.push_back(forSystem(P(phaseShift), target, size));
    gates.push_back("P(" + std::to_string(phaseShift) + ", " + std::to_string(target) + ")");
} // Phase shift
void Circuit::t(size_t target) {
    matrices.push_back(forSystem(P(M_PI * 0.25), target, size));
    gates.push_back("T("+ std::to_string(target) + ")");
} // T gate
void Circuit::tDagger(size_t target) {
    matrices.push_back(forSystem(P(-M_PI * 0.25), target, size));
    gates.push_back("T†(" + std::to_string(target) + ")");
} // T gate
void Circuit::cnot(size_t control, size_t target) {
    matrices.push_back(CNOT(control, target, size));
    gates.push_back("CNOT(" + std::to_string(control) + ", " + std::to_string(target) + ")");
} // Controled not
void Circuit::ccnot(size_t control1, size_t control2, size_t target) {
    h(target);
    cnot(control2, target);
    tDagger(target);
    cnot(control1, target);
    t(target);
    cnot(control2, target);
    tDagger(target);
    cnot(control1, target);
    t(control2);
    t(target);
    cnot(control1, control2);
    h(target);
    t(control1);
    tDagger(control2);
    cnot(control1, control2);
} // Toffoli gate
void Circuit::cp(double phi, size_t target1, size_t target2) {
    matrices.push_back(CPHASE(phi, target1, target2, size));
    gates.push_back("CP(" + std::to_string(phi) + ", "
    + std::to_string(target1)+ ", " + std::to_string(target2) + ")");
} // Controlled phase rotation

// composed gates
void Circuit::add(size_t bits) {
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
void Circuit::qft(size_t first, size_t last, bool approximate) {
    int threshold = (int)log2(last - first) + 1;
    for(int i = 0; i < last - first; i++) {
        h(i + first);
        for(int k = 2; k + i <= last - first; k++) {
            if(approximate && k > threshold)
                break;
            double tmp = (1.0 / (1 << k));
            cp(2 * M_PI * tmp, first + i, first + k + i - 1);
        }
    }
}
void Circuit::iqft(size_t first, size_t last, bool approximate) {
    int threshold;
    if(approximate)
        threshold = (int)log2(last - first) + 1;
    else
        threshold = INT_MAX; // just a big number
    for(int i = (int)(last - first) - 1; i >= 0; i--) {
        for(int k = std::min((int)(last - first) - i, threshold); k >= 2; k--) {
            double tmp = (1.0 / (1 << k));
            cp(-2 * M_PI * tmp, first + i, first + k + i - 1);
        }
        h(first + i);
    }
}
void Circuit::qadd(size_t firstQubit, size_t bits, bool approximate) {
    if(2 * bits > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");
    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (i + 1)));
            cp(2 * M_PI * tmp, j + firstQubit,  j + bits - i + firstQubit);
        }
    }
}
void Circuit::iqadd(size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");
    
    int threshold;
    if (approximate)
        threshold = (int)log2(bits) + 1;
    else
        threshold = bits - 1;
    
    for (int i = bits - 1; i >= 0; i--) {
        for (int j = threshold; j >= 0; j--) {
            if (approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (i + 1)));
            cp(-2 * M_PI * tmp, j + firstQubit, j + bits - i + firstQubit);
        }
    }
}
void Circuit::qaddMod(size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + 3 + firstQubit > size)
        throw std::out_of_range("qaddMod gate requires at least 2*bits + 3 qubits");

}

void Circuit::print() {
    for(auto s: gates) {
        std::cout << s << std::endl;
    }
}
