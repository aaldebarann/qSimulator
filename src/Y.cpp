//
// Created by aleksei on 28.05.23.
//

#include "gates/Y.h"

namespace gates {

    Matrix Y::matrix() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        Complex i(0, 1);
        matrix(0, 1) = -i;
        matrix(1, 0) = i;
        return matrix;
    }

    Y::Y(size_t target) : target(target), SingleQubitGate(target) {}
} // gates