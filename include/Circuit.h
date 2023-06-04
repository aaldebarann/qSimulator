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

    void i(size_t target);
    void x(size_t target);
    void y(size_t target);
    void z(size_t target);
    void h(size_t target);
    void p(Complex phaseShift, size_t target);
    void cnot(size_t control, size_t target);

    vector<Matrix> getMatrices() {
        return v;
    };
};

#endif //QSIMULATOR_CIRCUIT_H
