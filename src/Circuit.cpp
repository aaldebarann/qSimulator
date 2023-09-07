//
// Created by aleksei on 04.06.23.
//

#include "Circuit.h"
#include "Gates.h"
#include <cmath>
#include <iostream>
#include <climits>
// #include <corecrt_math_defines.h>

//#define HIGH_LEVEL_GATES_LOG

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
    gates.push_back("X(" + std::to_string(target) + ")");
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
    gates.push_back("T�(" + std::to_string(target) + ")");
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
void Circuit::ccp(double phi, size_t control1, size_t control2, size_t target) {
    matrices.push_back(CCP(phi, control1, control2, target, size));
    gates.push_back("CCP(" + std::to_string(phi) + ", "
        + std::to_string(control1) + ", " + std::to_string(control2) + ", " + std::to_string(target) + ")");
} // Controlled phase rotation
void Circuit::cccp(double phi, size_t control1, size_t control2, size_t control3, size_t target) {
    matrices.push_back(CCCP(phi, control1, control2, control3, target, size));
    gates.push_back("CCCP(" + std::to_string(phi) + ", "
        + std::to_string(control1) + ", " + std::to_string(control2) + ", " + std::to_string(control3) + ", " + std::to_string(target) + ")");

}
void Circuit::cswap(size_t control, size_t target1, size_t target2) {
    cnot(target2, target1);
    ccnot(control, target1, target2);
    cnot(target2, target1);
    // matrices.push_back(CSWAP( control, target1, target2, size));
    gates.push_back("CSWAP(" + std::to_string(control) + ", "
                    + std::to_string(target1)+ ", " + std::to_string(target2) + ")");
}
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
    if (last - 1 > size)
        throw std::out_of_range("qft out of range");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("QFT(" + std::to_string(first) + ", "
                    + std::to_string(last)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold = (int)log2(last - first + 1) + 2;
    for(int i = 0; i < last - first; i++) {
        h(i + first);
        for(int k = 2; k + i <= last - first; k++) {
            if(approximate && k > threshold)
                break;
            double tmp = (1.0 / (1 << k));
            cp(2 * M_PI * tmp, first + i, first + k + i - 1);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::iqft(size_t first, size_t last, bool approximate) {
    if (last - 1 > size)
        throw std::out_of_range("iqft out of range");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("QFT-1(" + std::to_string(first) + ", "
                    + std::to_string(last)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold;
    if(approximate)
        threshold = (int)log2(last - first + 1) + 2;
    else
        threshold = INT_MAX; // just a big number
    for(int i = (int)(last - first) - 1; i >= 0; i--) {
        for(int k = std::min((int)(last - first) - i, threshold); k >= 2; k--) {
            double tmp = (1.0 / (1 << k));
            cp(-2 * M_PI * tmp, first + i, first + k + i - 1);
        }
        h(first + i);
    }

#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}

void Circuit::qadd(size_t firstQubit, size_t bits, bool approximate) {
    if(2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n + 1 bits for two n-bit numbers");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qADD(" + std::to_string(firstQubit) + ", "
                    + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            cp(2 * M_PI * tmp, j + i + firstQubit,  bits + i + firstQubit);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::iqadd(size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits for two n-bit numbers");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qADD-1(" + std::to_string(firstQubit) + ", "
                    + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold  = (int)log2(bits) + 1;

    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            cp(-2 * M_PI * tmp, j + i + firstQubit, bits + i + firstQubit);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}

void Circuit::qadd_1c(size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qADD_1c(" + std::to_string(control) + ", "+ std::to_string(firstQubit) + ", "
                    + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            ccp(2 * M_PI * tmp, control, j + i + firstQubit,  bits + i + firstQubit);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::iqadd_1c(size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qADD_1c-1(" + std::to_string(control) + ", "+ std::to_string(firstQubit) + ", "
                    + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold  = (int)log2(bits) + 1;
    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            ccp(-2 * M_PI * tmp, control, j + i + firstQubit, bits + i + firstQubit);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::qadd_2c(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit > size)
        throw std::out_of_range("qadd_2c out of range");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qADD_2c(" + std::to_string(control1) + ", "+  std::to_string(control2)+ ", "+ std::to_string(firstQubit) + ", "
                    + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif

    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            cccp(2 * M_PI * tmp, control1, control2, j + i + firstQubit,  bits + i + firstQubit);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::iqadd_2c(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");

#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qADD_2c-1(" + std::to_string(control1) + ", "+ std::to_string(control2)+ + ", "+ std::to_string(firstQubit) + ", "
                    + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    int threshold  = (int)log2(bits) + 1;
    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            cccp(-2 * M_PI * tmp, control1, control2, j + i + firstQubit, bits + i + firstQubit);
        }
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::qaddMod_2c(unsigned a, unsigned N, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    bits++; // one extra bit to avoid overflow
    if (2 * bits + firstQubit + 1 > size)
        throw std::out_of_range("qaddMod_2c out of range");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("qaddMod_2c(" + std::to_string(a) + std::to_string(N) + ", "+ ", "+
    std::to_string(control1) + ", "+ std::to_string(control2)+ + ", "+ std::to_string(firstQubit)
    + ", " + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    unsigned aCopy = a, NCopy = N;
    // �ADD(a)
    for (int i = 0; i < bits; i++) {
        if (a % 2 == 1)
            x(bits - i - 1 + firstQubit);
        a /= 2;
    }
    a = aCopy;
    qadd_2c(control1, control2, firstQubit, bits, approximate);
    // inverse qADD(N)
    for (int i = 0; i < bits; i++) {
        if (N % 2 != a % 2)
            x(bits - i - 1 + firstQubit);
        N /= 2;
        a /= 2;
    }
    N = NCopy;
    a = aCopy;
    iqadd(firstQubit, bits, approximate);

    iqft(firstQubit + bits, firstQubit + 2*bits, approximate);
    cnot(firstQubit + bits, firstQubit + 2*bits);
    qft(firstQubit + bits, firstQubit + 2*bits, approximate);
    
    // �ADD(N)
    // N is already in register 
    qadd_1c(firstQubit + 2*bits, firstQubit, bits, approximate);
    // inverse �ADD(a)
    for (int i = 0; i < bits; i++) {
        if (N % 2 != a % 2)
            x(bits - i - 1 + firstQubit);
        N /= 2;
        a /= 2;
    }
    N = NCopy;
    a = aCopy;
    iqadd_2c(control1, control2, firstQubit, bits, approximate);
    iqft(firstQubit + bits, 2*bits + firstQubit, approximate);
    x(firstQubit + bits);
    cnot(firstQubit + bits, firstQubit + 2*bits);
    x(firstQubit + bits);
    qft(firstQubit + bits, firstQubit + 2*bits, approximate);
    // �ADD(a)
    // a is already in register
    qadd_2c(control1, control2, firstQubit, bits, approximate);

    for (int i = 0; i < bits; i++) {
        if (a % 2 == 1)
            x(bits - i - 1 + firstQubit);
        a /= 2;
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}
void Circuit::iqaddMod_2c(unsigned int a, unsigned int N, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    bits++; // one extra bit to avoid overflow
    if (2 * bits + firstQubit + 1 > size)
        throw std::out_of_range("iqaddMod_2c out of range");
#ifdef HIGH_LEVEL_GATES_LOG
    gates.push_back("iqaddMod_2c(" + std::to_string(a) + std::to_string(N) + ", "+ ", "+
    std::to_string(control1) + ", "+ std::to_string(control2)+ + ", "+ std::to_string(firstQubit)
    + ", " + std::to_string(bits)+ ", " + std::to_string(approximate) + ")");
    gates.emplace_back("{");
#endif
    unsigned aCopy = a, NCopy = N;

    // put a in register
    for (int i = 0; i < bits; i++) {
        if (a % 2 == 1)
            x(bits - i - 1 + firstQubit);
        a /= 2;
    }
    a = aCopy;
    iqadd_2c(control1, control2, firstQubit, bits, approximate);
    iqft(firstQubit + bits, firstQubit + 2*bits, approximate);
    x(firstQubit + bits);
    cnot(firstQubit + bits, firstQubit + 2*bits);
    x(firstQubit + bits);
    qft(firstQubit + bits, 2*bits + firstQubit, approximate);
    qadd_2c(control1, control2, firstQubit, bits, approximate);
    // put N in register
    for (int i = 0; i < bits; i++) {
        if (N % 2 != a % 2)
            x(bits - i - 1 + firstQubit);
        N /= 2;
        a /= 2;
    }
    N = NCopy;
    a = aCopy;
    iqadd_1c(firstQubit + 2*bits, firstQubit, bits, approximate);
    iqft(firstQubit + bits, firstQubit + 2*bits, approximate);
    cnot(firstQubit + bits, firstQubit + 2*bits);
    qft(firstQubit + bits, firstQubit + 2*bits, approximate);
    qadd(firstQubit, bits, approximate);
    // put a in register
    for (int i = 0; i < bits; i++) {
        if (N % 2 != a % 2)
            x(bits - i - 1 + firstQubit);
        N /= 2;
        a /= 2;
    }
    N = NCopy;
    a = aCopy;
    iqadd_2c(control1, control2, firstQubit, bits, approximate);

    for (int i = 0; i < bits; i++) {
        if (a % 2 == 1)
            x(bits - i - 1 + firstQubit);
        a /= 2;
    }
#ifdef HIGH_LEVEL_GATES_LOG
    gates.emplace_back("}");
#endif
}

void Circuit::cMultMod(unsigned a, unsigned N, size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (2 * (bits + 1) + bits + firstQubit + 1> size)
        throw std::out_of_range("cMultMod out of range");

    qft(firstQubit + 2*bits + 1, firstQubit + 3*bits + 2, approximate);
    for(int i = 0; i < bits; i++) {
        qaddMod_2c((1 << i) * a, N, control, firstQubit + bits - i - 1, firstQubit + bits, bits, approximate);
    }
    iqft(firstQubit + 2*bits + 1, firstQubit + 3*bits + 2, approximate);
}
void Circuit::icMultMod(unsigned a, unsigned N, size_t control, size_t firstQubit, size_t bits,
                        bool approximate) {
    if (2 * (bits + 1) + bits + firstQubit + 1> size)
        throw std::out_of_range("icMultMod out of range");

    qft(firstQubit + 2*bits + 1, firstQubit + 3*bits + 2, approximate);
    for(int i = 0; i < bits; i++) {
        iqaddMod_2c((1 << i) * a, N, control, firstQubit + bits - i - 1, firstQubit + bits, bits, approximate);
    }
    iqft(firstQubit + 2*bits + 1, firstQubit + 3*bits + 2, approximate);

}
int64_t inverse(int64_t a, int64_t m) {
    // m > 1
    int64_t a1, a2, tmp, r, q, b = m;
    a1 =  1;
    a2 =  0;
    r = a % b;
    q = a / b;
    while(r != 0) {
        a = b;
        b = r;
        r = a % b;
        tmp = a1 - a2 * q;
        a1 = a2;
        a2 = tmp;
        q = a / b;
    }
    if(a2 < 0)
        a2 += m;
    return a2;
} // returns modular inverse
void Circuit::u(unsigned a, unsigned N, size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (3 * bits + firstQubit + 3 > size)
        throw std::out_of_range("controlled-U(a) out of range");
    cMultMod(a, N, control, firstQubit, bits, approximate);
    for(int i = 0; i < bits; i++) {
        cswap(control, firstQubit + i, firstQubit + 2*bits + 2 + i);
    }
    icMultMod(inverse(a, N), N, control, firstQubit, bits, approximate);
}

void Circuit::print() {
    for(auto s: gates) {
        std::cout << s << std::endl;
    }
}


