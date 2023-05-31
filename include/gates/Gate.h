//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_GATE_H
#define QSIMULATOR_GATE_H

#include "Matrix.h"

class Gate {
protected:
    Matrix I() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        return matrix;
    } // Identity matrix
    Matrix X() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        matrix(0, 1) = matrix(1, 0) = 1;
        return matrix;
    } // NOT matrix
public:
    virtual Matrix getMatrix(size_t systemSize) = 0;

    virtual ~Gate() = default;
};

#endif //QSIMULATOR_GATE_H
