//
// Created by Алексей on 15.05.2023.
//
#pragma once
#ifndef QSIMULATOR_GATES_H
#define QSIMULATOR_GATES_H

#include "Matrix.h"
#include <cmath>

// functions return matrix for quantum gates
Matrix I(); // Identity gate
Matrix X(); // NOT gate or Pauli-X
Matrix Y(); // Pauli-Y gate
Matrix Z(); // Pauli-Z gate
Matrix H(); // Hadamard gate
Matrix P(Complex phi); // Phase shift gate
Matrix CNOT(size_t control, size_t target, size_t systemSize); // cnot gate
Matrix CCNOT(size_t control1, size_t control2, size_t target, size_t systemSize); // ccnot gate (toffoli gate)

// matrix for n-dimensional system
Matrix forSystem(Matrix singleQubitMatrix, size_t targetQubit, size_t systemSize);

#endif //QSIMULATOR_GATES_H
