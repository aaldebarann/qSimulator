//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_X_H
#define QSIMULATOR_X_H

#include "SingleQubitGate.h"

namespace gates {
    // NOT gate or Pauli-X gate
    class X: public SingleQubitGate {
    private:
        Matrix matrix() override; // matrix of H gate
    public:
        const size_t target; // target qubit number

        explicit X(size_t target);
        ~X() override = default;
    };

} // gates

#endif //QSIMULATOR_X_H
