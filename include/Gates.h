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

// functions return matrix for quantum gates in n-dimensional system
Matrix I(size_t target, size_t numberOfQubits); // Identity gate
Matrix X(size_t target, size_t numberOfQubits); // NOT gate or Pauli-X
Matrix Y(size_t target, size_t numberOfQubits); // Pauli-Y gate
Matrix Z(size_t target, size_t numberOfQubits); // Pauli-Z gate
Matrix H(size_t target, size_t numberOfQubits); // Hadamard gate
Matrix P(size_t target, Complex phi, size_t numberOfQubits); // Phase shift gate
Matrix CNOT(size_t control, size_t target, size_t numberOfQubits); // CNOT gate

#endif //QSIMULATOR_GATES_H
