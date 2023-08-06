//
// Created by aleksei on 04.06.23.
//

#ifndef QSIMULATOR_CIRCUIT_H
#define QSIMULATOR_CIRCUIT_H

#include "Matrix.h"
#include <string>
using std::string;

class Circuit {
    vector<Matrix*> v; // вектор из матриц гейтов
    vector<string> gates; // вектор из строк с поисаниями гейтов
public:
    const size_t size;
    void print();

    explicit Circuit(size_t size);
    ~Circuit() = default;
    // base quantum gates
    void i(size_t target); // Identity gate
    void x(size_t target); // NOT gate (Pauli-X)
    void y(size_t target); // Pauli-Y
    void z(size_t target); // Pauli-Z
    void h(size_t target); // Hadamar gate
    void p(double phaseShift, size_t target); // Phase shift
    void cnot(size_t control, size_t target); // Controlled not gate
    void ccnot(size_t control1, size_t control2, size_t target); // ccnot gate (toffoli gate)
    void cp(double phi, size_t target1, size_t target2); // Controlled phase rotation
    // classical addition
    void add_classic(size_t bits);
    void add_quantum(size_t bits, bool approximate = false);
    // QFT
    // from first qubit to last - 1 qubit
    void qft(size_t first, size_t last, bool approximate = false);
    void iqft(size_t first, size_t last, bool approximate = false);

    vector<Matrix*> getMatrices() {
        return v;
    };
};

#endif //QSIMULATOR_CIRCUIT_H
