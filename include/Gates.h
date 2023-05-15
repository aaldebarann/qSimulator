//
// Created by Алексей on 15.05.2023.
//
#pragma once

#include "Matrix.h"
#include <cmath>

// functions return matrix for quantum gates

Matrix I() {
    Matrix matrix(2);
    matrix(0, 0) = matrix(1, 1) = 1;
    matrix(0, 1) = matrix(1, 0) = 0;
    return matrix;
} // Identity gate
Matrix X() {
    Matrix matrix(2);
    matrix(0, 0) = matrix(1, 1) = 0;
    matrix(0, 1) = matrix(1, 0) = 1;
    return matrix;
} // NOT gate or Pauli-X
Matrix Y() {
    Matrix matrix(2);
    matrix(0, 0) = matrix(1, 1) = 0;
    complex<float> i(0, 1);
    matrix(0, 1) = -i;
    matrix(1, 0) = i;
    return matrix;
} // Pauli-Y
Matrix Z() {
    Matrix matrix(2);
    matrix(0, 0) = 1;
    matrix(0, 1) = matrix(1, 0) = 0;
    matrix(1, 1) = -1;
    return matrix;
} // Pauli-Z
Matrix H() {
    Matrix matrix(2);
    float tmp = 1.0 / sqrt(2);
    matrix(0, 0) =  matrix(0, 1) = matrix(1, 0) = tmp;
    matrix(1, 1) = -tmp;
    return matrix;
} // Hadamard
Matrix P(complex<float> phi) {
    Matrix matrix(2);
    complex<float> i(0, 1);
    matrix(0, 0) = 1;
    matrix(0, 1) = matrix(1, 0) = 0;
    matrix(1, 1) = std::exp(phi * i);
    return matrix;
}
*/

#endif //QSIMULATOR_GATES_H
