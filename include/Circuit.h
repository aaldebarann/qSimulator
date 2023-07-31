//
// Created by aleksei on 04.06.23.
//

#ifndef QSIMULATOR_CIRCUIT_H
#define QSIMULATOR_CIRCUIT_H

#include "Matrix.h"

class Circuit {
    vector<Matrix> v;
public:
    const size_t size;

    explicit Circuit(size_t size);
    ~Circuit() = default;
    // base quantum gates
    void i(size_t target); // Identity gate
    void x(size_t target); // NOT gate (Pauli-X)
    void y(size_t target); // Pauli-Y
    void z(size_t target); // Pauli-Z
    void h(size_t target); // Hadamar gate
    void p(Complex phaseShift, size_t target); // Phase shift
    void cnot(size_t control, size_t target); // Controlled not gate
    void ccnot(size_t control1, size_t control2, size_t target); // ccnot gate (toffoli gate)
    void cp(Complex phi, size_t target1, size_t target2); // Controlled phase rotation
    // classical addition
    void add_classic(size_t bits);
    void add_quantum(size_t bits);
    void add_quantum_approximate(size_t bits);
    // QFT
    // from first qubit to last - 1 qubit
    void qft(size_t first, size_t last);
    void iqft(size_t first, size_t last);
    void qft_approximate(size_t first, size_t last);
    void iqft_approximate(size_t first, size_t last);

    vector<Matrix> getMatrices() {
        return v;
    };
};

#endif //QSIMULATOR_CIRCUIT_H
