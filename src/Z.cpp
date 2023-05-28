//
// Created by aleksei on 28.05.23.
//

#include "gates/Z.h"

namespace gates {
    Matrix Z::matrix() {
        Matrix matrix(2);
        matrix(0, 0) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        matrix(1, 1) = -1;
        return matrix;
    }

    Z::Z(size_t target) : target(target), SingleQubitGate(target) {}
} // gates