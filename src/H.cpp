//
// Created by aleksei on 28.05.23.
//

#include "gates/H.h"

namespace gates {

    Matrix H::matrix() {
        Matrix matrix(2);
        double tmp = 1.0 / sqrt(2);
        matrix(0, 0) =  matrix(0, 1) = matrix(1, 0) = tmp;
        matrix(1, 1) = -tmp;
        return matrix;
    }
    H::H(size_t target) : target(target), SingleQubitGate(target) {}
} // gates