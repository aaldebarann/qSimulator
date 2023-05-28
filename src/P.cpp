//
// Created by aleksei on 28.05.23.
//

#include "gates/P.h"

namespace gates {
    Matrix P::matrix() {
        Matrix matrix(2);
        Complex i(0, 1);
        matrix(0, 0) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        matrix(1, 1) = std::exp(phi * i);
        return matrix;
    }

    P::P(size_t target, Complex phi): SingleQubitGate(target), target(target), phi(phi) {}
} // gates