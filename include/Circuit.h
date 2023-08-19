//
// Created by aleksei on 04.06.23.
//

#ifndef QSIMULATOR_CIRCUIT_H
#define QSIMULATOR_CIRCUIT_H

#include "Matrix.h"
#include <string>
using std::string;

class Circuit {
    vector<Matrix*> matrices; // вектор из матриц гейтов
    vector<string> gates; // вектор из строк с поисаниями гейтов
public:
    const size_t size;
    void print();

    explicit Circuit(size_t size);
    ~Circuit();
    // base quantum gates
    void i(size_t target); // Identity gate
    void x(size_t target); // NOT gate (Pauli-X)
    void y(size_t target); // Pauli-Y
    void z(size_t target); // Pauli-Z
    void h(size_t target); // Hadamar gate
    void p(double phaseShift, size_t target); // Phase shift
    void t(size_t target); // T gate
    void tDagger(size_t target); // Hermitian transpose of T gate 
    void cnot(size_t control, size_t target); // Controlled not gate
    void ccnot(size_t control1, size_t control2, size_t target); // ccnot gate (toffoli gate)
    void cp(double phi, size_t target1, size_t target2); // Controlled phase rotation
    void add(size_t bits); // classical addition
    // QFT
    // from first qubit to last - 1 qubit
    void qft(size_t first, size_t last, bool approximate = false);
    void iqft(size_t first, size_t last, bool approximate = false);

    void qadd(size_t firstQubit, size_t bits, bool approximate = false); // quantum addition
    void iqadd(size_t firstQubit, size_t bits, bool approximate = false); // inverse quantum addition
    
    void qaddMod(size_t firstQubit, size_t bits, bool approximate = false);
    void iqaddMod(size_t firstQubit, size_t bits, bool approximate = false);

    vector<Matrix*> getMatrices() {
        return matrices;
    };
};

#endif //QSIMULATOR_CIRCUIT_H
