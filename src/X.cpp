//
// Created by aleksei on 28.05.23.
//

#include "gates/X.h"

namespace gates {
    Matrix X::matrix() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        matrix(0, 1) = matrix(1, 0) = 1;
        return matrix;
    }

    X::X(size_t target) : target(target), SingleQubitGate(target) {}
} // gates