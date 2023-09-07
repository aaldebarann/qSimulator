//
// Created by Алексей on 15.05.2023.
//
#pragma once
#ifndef QSIMULATOR_GATES_H
#define QSIMULATOR_GATES_H

#include "Matrix.h"
#include <cmath>

// functions return matrix for quantum gates

// single-qubit gates
Matrix I(); // Identity gate
Matrix X(); // NOT gate or Pauli-X
Matrix Y(); // Pauli-Y gate
Matrix Z(); // Pauli-Z gate
Matrix H(); // Hadamard gate
Matrix P(Complex phi); // Phase shift gate
// matrix for n-dimensional system
Matrix* forSystem(Matrix singleQubitMatrix, size_t targetQubit, size_t systemSize);
// multiple-qubit gates
Matrix* CNOT(size_t control, size_t target, size_t systemSize); // Controlled not gate
Matrix* CCNOT(size_t control1, size_t control2, size_t target, size_t systemSize); // ccnot gate (toffoli gate)
Matrix* CPHASE(Complex phi, size_t target1, size_t target2, size_t systemSize); // Controlled phase rotation
Matrix* CCP(double phi, size_t target1, size_t target2, size_t target3, size_t systemSize);
Matrix* CCCP(double phi, size_t control1, size_t control2, size_t control3, size_t target, size_t systemSize);
Matrix* CSWAP(size_t control, size_t target1, size_t target2, size_t systemSize);
                                                                                /*
Matrix* CСPHASE(Complex phi, size_t control1, size_t control2, size_t target, size_t systemSize); // Controlled phase rotation
Matrix* CССP(Complex phi, size_t control1, size_t control2, size_t control3, size_t target, size_t systemSize); // Controlled phase rotation
*/

#endif //QSIMULATOR_GATES_H
