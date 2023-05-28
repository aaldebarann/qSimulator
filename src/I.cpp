//
// Created by aleksei on 28.05.23.
//

#include "gates/I.h"

namespace gates {
    Matrix I::matrix() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        return matrix;
    }

    I::I(size_t target) : SingleQubitGate(target), target(target) {}
} // gates