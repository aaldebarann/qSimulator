//
// Created by aleksei on 04.06.23.
//

#ifndef QSIMULATOR_CIRCUIT_H
#define QSIMULATOR_CIRCUIT_H

#include "Matrix.h"

class Circuit {
    Matrix* matrix;
public:
    const size_t size;

    explicit Circuit(size_t size);
    ~Circuit() = default;
    // base quantum gates
    void i(size_t target);
    void x(size_t target);
    void y(size_t target);
    void z(size_t target);
    void h(size_t target);
    void p(Complex phaseShift, size_t target);
    void cnot(size_t control, size_t target);
    void ccnot(size_t control1, size_t control2, size_t target);
    // classical addition
    void add(size_t bits);

    Matrix getMatrix() {
        return *matrix;
    };
};

#endif //QSIMULATOR_CIRCUIT_H
