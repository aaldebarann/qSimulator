//
// Created by aleksei on 9/8/23.
//

#include <climits>
#include <cmath>
#include "StateVector.h"
#include <bitset> // TODO

StateVector::StateVector(size_t sz): size(sz) {
    state.resize(1 << size);
    for(Complex z: state)
        z = 0;
    state[0] = 1;
}

// StateVector measure
size_t StateVector::measure() const {
    double r = (double)std::rand() / RAND_MAX;
    double sum = 0;
    for(int j = 0; j < state.size(); j++) {
        sum += std::abs(state[j].real()*state[j].real());
        sum += std::abs(state[j].imag()*state[j].imag());
        if(r < sum)
            return j;
    }
    return state.size() - 1;
}
// System
vector<Complex> StateVector::measure(size_t target) {
    double amplitude0 = 0;
    size_t n = state.size();
    for(int i = 0; i < n; i++) {
        if ((i & (1 << target)) == 0) {
            amplitude0 += state[i].real()*state[i].real();
            amplitude0 += state[i].imag()*state[i].imag();
        }
    }
    double r = (double)std::rand() / RAND_MAX;
    if(r < amplitude0) {
        // target qubit is in state |0>
        for(int i = 0; i < n; i++) {
            if ((i & (1 << target)) != 0) {
                state[i] = 0;
            }
        }
    } else {
        // target qubit is in state |1>
        for(int i = 0; i < n; i++) {
            if ((i & (1 << target)) == 0) {
                state[i] = 0;
            }
        }
    }
    vector<Complex> v1 = getState();
    for(Complex u: v1)
        std::cout << u << "  ";
    std::cout << std::endl;
    // normalization
    double norm = 0;
    for(int i = 0; i < n; i++) {
        norm += state[i].real() * state[i].real();
        norm += state[i].imag() * state[i].imag();
    }
    norm = std::sqrt(norm);
    for(int i = 0; i < n; i++) {
        state[i] /= norm;
    }
    return state;
}

// Basic gates
void StateVector::i(size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    gates.push_back("I(" + std::to_string(target) + ")");
} // Identity gate
void StateVector::x(size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    gates.push_back("X(" + std::to_string(target) + ")");
    size_t mask = 1 << target;
    for(size_t j = 0; j < (1 << (target)); j++) {
        for(size_t k = 0; k < (1 << (size - target - 1)); k++) {
            size_t t = j + (k << (target + 1));
            // applying gate
            std::swap(state[t], state[t ^ mask]);
        }
    }
} // NOT gate (Pauli-X)
void StateVector::y(size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    gates.push_back("Y(" + std::to_string(target) + ")");
    size_t mask = 1 << target;
    Complex i(0, 1);
    for(size_t j = 0; j < (1 << (target)); j++) {
        for(size_t k = 0; k < (1 << (size - target - 1)); k++) {
            size_t t = j + (k << (target + 1));
            // applying gate
            std::swap(state[t], state[t ^ mask]);
            state[t] *= -i;
            state[t ^ mask] *= i;
        }
    }
} // Pauli-Y
void StateVector::z(size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    gates.push_back("Z(" + std::to_string(target) + ")");
    size_t mask = 1 << target;
    for(size_t j = 0; j < (1 << (target)); j++) {
        for(size_t k = 0; k < (1 << (size - target - 1)); k++) {
            size_t t = j + (k << (target + 1));
            // applying gate
            state[t ^ mask] *= -1;
        }
    }
} // Pauli-Z
void StateVector::h(size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    gates.push_back("H(" + std::to_string(target) + ")");
    size_t mask = 1 << target;
    for(size_t j = 0; j < (1 << (target)); j++) {
        for(size_t k = 0; k < (1 << (size - target - 1)); k++) {
            size_t t = j + (k << (target + 1));
            // applying gate
            Complex x1 = state[t];
            Complex x2 = state[t ^ mask];
            Complex tmp (1.0 / std::sqrt(2), 0);
            state[t] = (x1 + x2) * tmp;
            state[t ^ mask] = (x1 - x2) * tmp;
        }
    }
} // Hadamar gate
void StateVector::p(double phaseShift, size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    gates.push_back("P(" + std::to_string(phaseShift) + ", " + std::to_string(target) + ")");
    size_t mask = 1 << target;
    Complex tmp(0, phaseShift);
    for(size_t j = 0; j < (1 << size); j++) {
        if((j & mask) == mask){
            // applying gate
            state[j] *= std::exp(tmp);
        }
    }
} // Phase shift
void StateVector::t(size_t target) {
    p(M_PI * 0.25, target);
} // T gate
void StateVector::it(size_t target) {
    p(-M_PI * 0.25, target);
} // T gate
void StateVector::cnot(size_t control, size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    if(control >= size)
        throw std::out_of_range("control qubit index is out of range");
    if(target == control)
        throw std::invalid_argument("target qubit must be different from control qubit");
    gates.push_back("CNOT(" + std::to_string(control) + ", " + std::to_string(target) + ")");
    size_t mask = 1 << target;
    size_t controlMask = 1 << control;
    for(size_t j = 0; j < (1 << (target)); j++) {
        for(size_t k = 0; k < (1 << (size - target - 1)); k++) {
            size_t t = j + (k << (target + 1));
            // applying gate
            if((t & controlMask) > 0)
                std::swap(state[t], state[t ^ mask]);
        }
    }
} // Controled not
void StateVector::ccnot(size_t control1, size_t control2, size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    if(control1 >= size || control2 >= size)
        throw std::out_of_range("control qubit index is out of range");
    if(target == control1 || target == control2)
        throw std::invalid_argument("target qubit must be different from control qubit");
    if(control1 == control2)
        throw std::invalid_argument("control qubits indexes should not match");
    h(target);
    cnot(control2, target);
    it(target);
    cnot(control1, target);
    t(target);
    cnot(control2, target);
    it(target);
    cnot(control1, target);
    t(control2);
    t(target);
    cnot(control1, control2);
    h(target);
    t(control1);
    it(control2);
    cnot(control1, control2);
} // Toffoli gate
void StateVector::cp(double phi, size_t control, size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    if(control >= size)
        throw std::out_of_range("control qubit index is out of range");
    if(target == control)
        throw std::invalid_argument("target qubit must be different from control qubit");
    size_t mask = (1 << target) + (1 << control);
    Complex tmp(0, phi);
    for(size_t j = 0; j < (1 << size); j++) {
        if((j & mask) == mask){
            // applying gate
            state[j] *= std::exp(tmp);
        }
    }
} // Controlled phase rotation
void StateVector::cry(double theta, size_t control, size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    if(control >= size)
        throw std::out_of_range("control qubit index is out of range");
    if(target == control)
        throw std::invalid_argument("target qubit must be different from control qubit");
    gates.push_back("CRY(" + std::to_string(theta) + ", "
        + std::to_string(control) + ", " + std::to_string(target) + ")");
    // size_t mask = 1 << target;
    // size_t controlMask = 1 << control;
    // for(size_t x = 0; x < (1 << size); x++) {
    //     std::cout << std::bitset<2>(x) << std::endl;
    //     if(x & mask == 1) {
    //         std::cout << "duplicated" << std::endl;
    //         continue;
    //     }
    //     if(x & controlMask == 1) {
    //         Complex a = state[x];
    //         Complex b = state[x | mask];           
    //         state[x] = a * (Complex)cos(theta / 2) - b * (Complex)sin(theta / 2);
    //         state[x | mask] = a * (Complex)sin(theta / 2) + b * (Complex)cos(theta / 2);
    //     } else 
    //         std::cout << "control is 0" << std::endl;
    // }
    size_t mask = 1 << target;
    size_t controlMask = 1 << control;
    for(size_t j = 0; j < (1 << (target)); j++) {
        for(size_t k = 0; k < (1 << (size - target - 1)); k++) {
            size_t t = j + (k << (target + 1));
            std::cout << std::bitset<4>(t) << std::endl;
            // applying gate
            if((t & controlMask) > 0) {     
                Complex a = state[t];
                Complex b = state[t ^ mask];           
                state[t] = a * (Complex)cos(theta / 2) - b * (Complex)sin(theta / 2);
                state[t ^ mask] = a * (Complex)sin(theta / 2) + b * (Complex)cos(theta / 2);
            }
        }
    }
} // Controlled phase rotation
void StateVector::ccp(double phi, size_t control1, size_t control2, size_t target) {
    if(target >= size)
        throw std::out_of_range("target qubit index is out of range");
    if(control1 >= size || control2 >= size)
        throw std::out_of_range("control qubit index is out of range");
    if(target == control1 || target == control2)
        throw std::invalid_argument("target qubit must be different from control qubit");
    if(control1 == control2)
        throw std::invalid_argument("control qubits indexes should not match");
    gates.push_back("CCP(" + std::to_string(phi) + ", "
                    + std::to_string(control1) + ", " + std::to_string(control2) + ", " + std::to_string(target) + ")");
    size_t mask = (1 << target) + (1 << control1) + (1 << control2);
    Complex tmp(0, phi);
    for(size_t j = 0; j < (1 << size); j++) {
        if((j & mask) == mask){
            // applying gate
            state[j] *= std::exp(tmp);
        }
    }
} // Controlled phase rotation
/*
void StateVector::cccp(double phi, size_t control1, size_t control2, size_t control3, size_t target) {
    gates.push_back("CCCP(" + std::to_string(phi) + ", "
                    + std::to_string(control1) + ", " + std::to_string(control2) + ", " + std::to_string(control3) + ", " + std::to_string(target) + ")");
    size_t mask = (1 << target) + (1 << control1) + (1 << control2) + (1 << control3);
    Complex tmp(0, phi);
    for(size_t j = 0; j < (1 << size); j++) {
        if((j & mask) == mask){
            // applying gate
            state[j] *= std::exp(tmp);
        }
    }
}
 */
void StateVector::cswap(size_t control, size_t target1, size_t target2) {
    cnot(target2, target1);
    ccnot(control, target1, target2);
    cnot(target2, target1);
    // matrices.push_back(CSWAP( control, target1, target2, size));
    gates.push_back("CSWAP(" + std::to_string(control) + ", "
                    + std::to_string(target1)+ ", " + std::to_string(target2) + ")");
}
// composed gates
void StateVector::add(size_t bits) {
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

void StateVector::qft(size_t first, size_t last, bool approximate) {
    if (last - 1 > size)
        throw std::out_of_range("qft out of range");
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
}
void StateVector::iqft(size_t first, size_t last, bool approximate) {
    if (last - 1 > size)
        throw std::out_of_range("iqft out of range");
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

}

void StateVector::qadd(size_t firstQubit, size_t bits, bool approximate) {
    if(2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n + 1 bits for two n-bit numbers");

    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            cp(2 * M_PI * tmp, j + i + firstQubit,  bits + i + firstQubit);
        }
    }
}
void StateVector::qadd(unsigned a, size_t firstQubit, size_t bits, bool approximate) {
    if(bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n + 1 bits for two n-bit numbers");

    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            if((a & (1 << (bits - j - i - 1)) ) > 0) {
                p(2 * M_PI * tmp, i + firstQubit);
            }
        }
    }

}
void StateVector::iqadd(size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits for two n-bit numbers");

    int threshold  = (int)log2(bits) + 1;

    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            cp(-2 * M_PI * tmp, j + i + firstQubit,  bits + i + firstQubit);
        }
    }

}
void StateVector::iqadd(unsigned a, size_t firstQubit, size_t bits, bool approximate) {
    if (bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits for two n-bit numbers");

    int threshold  = (int)log2(bits) + 1;

    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            if((a & (1 << (bits - j - i - 1)) ) > 0) {
                p(-2 * M_PI * tmp, i + firstQubit);
            }
        }
    }

}

void StateVector::qadd_1c(unsigned a, size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");

    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            if((a & (1 << (bits - j - i - 1)) ) > 0) {
                cp(2 * M_PI * tmp, control, i + firstQubit);
            }
        }
    }

}
void StateVector::iqadd_1c(unsigned a, size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");

    int threshold  = (int)log2(bits) + 1;
    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            if((a & (1 << (bits - j - i - 1)) ) > 0) {
                cp(-2 * M_PI * tmp, control, i + firstQubit);
            }
        }
    }

}
void StateVector::qadd_2c(unsigned a, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    if (bits + firstQubit > size)
        throw std::out_of_range("qadd_2c out of range");


    int threshold = (int)log2(bits) + 1;
    for(int i = 0; i < bits; i++) {
        for(int j = 0; j < bits - i; j++) {
            if(approximate && j > threshold)
                break;
            double tmp = (1.0 / (1 << (j + 1)));
            if((a & (1 << (bits - j - i - 1)) ) > 0) {
                ccp(2 * M_PI * tmp, control1, control2, i + firstQubit);
            }
        }
    }

}
void StateVector::iqadd_2c(unsigned a, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    if (bits + firstQubit > size)
        throw std::out_of_range("quantum addition requires 2n bits to add_classic two n-bit numbers");

    int threshold  = (int)log2(bits) + 1;
    for (int i = bits - 1; i >= 0; i--) {
        for (int j = bits - i - 1; j >= 0; j--) {
            if (approximate && j > threshold)
                continue;
            double tmp = (1.0 / (1 << (j + 1)));
            if((a & (1 << (bits - j - i - 1)) ) > 0) {
                ccp(-2 * M_PI * tmp, control1, control2, i + firstQubit);
            }
        }
    }
}
void StateVector::qaddMod_2c(unsigned a, unsigned N, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    a %= N;
    bits++; // one extra bit to avoid overflow
    if (bits + firstQubit + 1 > size)
        throw std::out_of_range("qaddMod_2c out of range");

    qadd_2c(a, control1, control2, firstQubit, bits, approximate);
    iqadd(N, firstQubit, bits, approximate);
    iqft(firstQubit, firstQubit + bits, approximate);
    cnot(firstQubit, firstQubit + bits);
    qft(firstQubit, firstQubit + bits, approximate);
    qadd_1c(N, firstQubit + bits, firstQubit, bits, approximate);
    iqadd_2c(a, control1, control2, firstQubit, bits, approximate);
    iqft(firstQubit, bits + firstQubit, approximate);
    x(firstQubit);
    cnot(firstQubit, firstQubit + bits);
    x(firstQubit);
    qft(firstQubit, firstQubit + bits, approximate);
    qadd_2c(a, control1, control2, firstQubit, bits, approximate);
}
void StateVector::iqaddMod_2c(unsigned int a, unsigned int N, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate) {
    a %= N;
    bits++; // one extra bit to avoid overflow
    if (bits + firstQubit + 1 > size)
        throw std::out_of_range("iqaddMod_2c out of range");

    iqadd_2c(a, control1, control2, firstQubit, bits, approximate);
    iqft(firstQubit, firstQubit + bits, approximate);
    x(firstQubit);
    cnot(firstQubit, firstQubit + bits);
    x(firstQubit);
    qft(firstQubit, bits + firstQubit, approximate);
    qadd_2c(a, control1, control2, firstQubit, bits, approximate);
    iqadd_1c(N, firstQubit + bits, firstQubit, bits, approximate);
    iqft(firstQubit, firstQubit + bits, approximate);
    cnot(firstQubit, firstQubit + bits);
    qft(firstQubit, firstQubit + bits, approximate);
    qadd(N, firstQubit, bits, approximate);
    iqadd_2c(a, control1, control2, firstQubit, bits, approximate);
}

void StateVector::cMultMod(unsigned a, unsigned N, size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if ( 2*bits + 2 + firstQubit > size)
        throw std::out_of_range("cMultMod out of range");

    qft(firstQubit + bits, firstQubit + 2*bits + 1, approximate);
    for(int i = 0; i < bits; i++) {
        qaddMod_2c((1 << i) * a, N, control, firstQubit + bits - i - 1, firstQubit + bits, bits, approximate);
    }
    iqft(firstQubit + bits, firstQubit + 2*bits + 1, approximate);
}
void StateVector::icMultMod(unsigned a, unsigned N, size_t control, size_t firstQubit, size_t bits,
                        bool approximate) {
    if ( 2*bits + 2 + firstQubit > size)
        throw std::out_of_range("icMultMod out of range");

    qft(firstQubit + bits, firstQubit + 2*bits + 1, approximate);
    for(int i = 0; i < bits; i++) {
        iqaddMod_2c((1 << i) * a, N, control, firstQubit + bits - i - 1, firstQubit + bits, bits, approximate);
    }
    iqft(firstQubit + bits, firstQubit + 2*bits + 1, approximate);

}
int64_t StateVector::inverse(int64_t a, int64_t m) {
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
void StateVector::u(unsigned a, unsigned N, size_t control, size_t firstQubit, size_t bits, bool approximate) {
    if (2 * bits + firstQubit + 2 > size)
        throw std::out_of_range("controlled-U(a) out of range");
    cMultMod(a, N, control, firstQubit, bits, approximate);
    for(int i = 0; i < bits; i++) {
        cswap(control, firstQubit + i, firstQubit + bits + 1 + i);
    }
    unsigned ia = inverse(a, N);
    icMultMod(ia, N, control, firstQubit, bits, approximate);
}

void StateVector::print() {
    for(auto s: gates) {
        std::cout << s << std::endl;
    }
}

// noise simulation
void StateVector::ampDamp(double gamma, size_t target, size_t ancillary) {
    double theta = asin(sqrt(gamma)) * 2; // sin^2(theta/2) = gamma
    // vector<Complex> v1 = getState();
    // for(Complex u: v1)
    //     std::cout << u << "  ";
    // std::cout << std::endl;
    // std::cout << "ampDamp(theta = "<<theta<<", target = "<<target<<", anc = "<<ancillary<<std::endl;
    cry(theta, target, ancillary);
    cnot(ancillary, target);
    measure(ancillary);
}
void StateVector::ampDamp(double gamma) {
    size_t m = size / 2;
    for(size_t i = 0; i < m; i++) {
        ampDamp(gamma, m + i, i);
    }
}