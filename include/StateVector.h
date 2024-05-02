//
// Created by aleksei on 9/8/23.
//

#ifndef QSIMULATOR_STATEVECTOR_H
#define QSIMULATOR_STATEVECTOR_H

#include <vector>
#include <iostream>

#include "Matrix.h"

using std::vector;
using std::string;

class StateVector {
private:
    vector<Complex> state;
    vector<string> gates; // вектор из строк с описаниями гейтов
    int64_t inverse(int64_t a, int64_t m);
public:
    const size_t size; // number of qubits
    explicit StateVector(size_t size);
    vector<Complex> getState() const {
        return state;
    } // returns current state
    void print();

    // system measure
    size_t measure() const; // system measure (doesn't change system state)
    vector<Complex> measure(size_t target); // single-qubit measure (changes system state)

    // applying quantum gates
    void i(size_t target); // Identity gate
    void x(size_t target); // NOT gate (Pauli-X)
    void y(size_t target); // Pauli-Y
    void z(size_t target); // Pauli-Z
    void h(size_t target); // Hadamar gate
    void p(double phaseShift, size_t target); // Phase shift
    void t(size_t target); // T gate
    void it(size_t target); // inverse T gate
    void cnot(size_t control, size_t target); // Controlled not gate
    void ccnot(size_t control1, size_t control2, size_t target); // ccnot gate (toffoli gate)
    void cp(double phi, size_t target1, size_t target2); // Controlled phase rotation

    void ccp(double phi, size_t control1, size_t control2, size_t target); // Phase rotation with two controll qubits
    // void cccp(double phi, size_t control1, size_t control2, size_t control3, size_t target);
    void cswap(size_t control, size_t target1, size_t target2);
    void add(size_t bits); // classical addition

    void qft(size_t first, size_t last, bool approximate = false); // from first qubit to last - 1 qubit
    void iqft(size_t first, size_t last, bool approximate = false); // from first qubit to last - 1 qubit

    void qadd(size_t firstQubit, size_t bits, bool approximate = false); // quantum addition
    void qadd(unsigned a, size_t firstQubit, size_t bits, bool approximate = false); // quantum addition
    void iqadd(size_t firstQubit, size_t bits, bool approximate = false); // inverse quantum addition
    void iqadd(unsigned a, size_t firstQubit, size_t bits, bool approximate = false); // inverse quantum addition

    void qadd_1c(unsigned a, size_t control, size_t firstQubit, size_t bits, bool approximate = false);
    void iqadd_1c(unsigned a, size_t control, size_t firstQubit, size_t bits, bool approximate = false);
    void qadd_2c(unsigned a, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);
    void iqadd_2c(unsigned a, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);
    void qaddMod_2c(unsigned summand, unsigned module, size_t control1, size_t control2, size_t firstQubit, size_t bits,
                    bool approximate = false);
    void iqaddMod_2c(unsigned summand, unsigned module, size_t control1, size_t control2, size_t firstQubit, size_t bits,
                     bool approximate = false);

    void cMultMod(unsigned a, unsigned module, size_t control, size_t firstQubit, size_t bits, bool approximate = false);
    void icMultMod(unsigned a, unsigned module, size_t control, size_t firstQubit, size_t bits, bool approximate = false);
    void u(unsigned a, unsigned module, size_t control, size_t firstQubit, size_t bits, bool approximate);

};


#endif //QSIMULATOR_STATEVECTOR_H
