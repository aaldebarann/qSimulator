//
// Created by aleksei on 04.06.23.
//

#ifndef QSIMULATOR_CIRCUIT_H
#define QSIMULATOR_CIRCUIT_H

#include "Matrix.h"
#include <string>
using std::string;

class Circuit {
private:
    vector<Matrix*> matrices; // вектор из матриц гейтов
    vector<string> gates; // вектор из строк с поисаниями гейтов
    
    void qadd_1c(size_t control, size_t firstQubit, size_t bits, bool approximate = false);
    void iqadd_1c(size_t control, size_t firstQubit, size_t bits, bool approximate = false);
    void qadd_2c(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);
    void iqadd_2c(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);
    
    // квантовое сложение с двумя контролирующими кубитами
    /*
    void qadd_1с(size_t control, size_t firstQubit, size_t bits, bool approximate = false); // quantum addition
    void qadd_2с(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false); // quantum addition
    void iqadd_2с(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false); // inverse quantum addition
    // квантовое сложение по модулю с двумя контролирующими кубитами
    void qaddMod_2c(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);
    void iqaddMod_2c(size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);
    */
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

    void ccp(double phi, size_t control1, size_t control2, size_t target); // Phase rotation with two controll qubits
    void cccp(double phi, size_t control1, size_t control2, size_t control3, size_t target);
                                                                           // void cccp(double phi, size_t control1, size_t control2, size_t control3, size_t target);
                                                                           //void cсcp(double phi, size_t control1, size_t control2, size_t control3, size_t target); // Phase rotation with three controll qubits
    void add(size_t bits); // classical addition
    // QFT
    // from first qubit to last - 1 qubit
    void qft(size_t first, size_t last, bool approximate = false);
    void iqft(size_t first, size_t last, bool approximate = false);

    void qadd(size_t firstQubit, size_t bits, bool approximate = false); // quantum addition
    void iqadd(size_t firstQubit, size_t bits, bool approximate = false); // inverse quantum addition

    void qaddMod_2c(unsigned summand, unsigned module, size_t control1, size_t control2, size_t firstQubit, size_t bits, bool approximate = false);


    vector<Matrix*> getMatrices() {
        return matrices;
    };
};

#endif //QSIMULATOR_CIRCUIT_H
