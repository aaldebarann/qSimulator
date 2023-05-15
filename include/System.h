//
// Created by Алексей on 15.05.2023.
//

#ifndef QSIMULATOR_SYSTEM_H
#define QSIMULATOR_SYSTEM_H

#include "Vector.h"
#include "Matrix.h"

class System {

    Vector* state;
public:
    const size_t size; // qubit number

    explicit System(size_t size);
    ~System();

    static Matrix I() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        return matrix;
    } // Identity gate
    static Matrix X() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        matrix(0, 1) = matrix(1, 0) = 1;
        return matrix;
    } // NOT gate or Pauli-X
    static Matrix Y() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        complex<float> i(0, 1);
        matrix(0, 1) = -i;
        matrix(1, 0) = i;
        return matrix;
    } // Pauli-Y
    static Matrix Z() {
        Matrix matrix(2);
        matrix(0, 0) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        matrix(1, 1) = -1;
        return matrix;
    } // Pauli-Z
    static Matrix H() {
        Matrix matrix(2);
        float tmp = 1.0 / sqrt(2);
        matrix(0, 0) =  matrix(0, 1) = matrix(1, 0) = tmp;
        matrix(1, 1) = -tmp;
        return matrix;
    } // Hadamard
    static Matrix P(complex<float> phi) {
        Matrix matrix(2);
        complex<float> i(0, 1);
        matrix(0, 0) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        matrix(1, 1) = std::exp(phi * i);
        return matrix;
    }

    Vector getState() {
        return *state;
    }
};


#endif //QSIMULATOR_SYSTEM_H
