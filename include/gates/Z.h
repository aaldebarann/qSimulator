//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_Z_H
#define QSIMULATOR_Z_H

#include "SingleQubitGate.h"

namespace gates {
    // Pauli-Z gate
    class Z: public SingleQubitGate {
    private:
        Matrix matrix() override; // matrix of H gate
    public:
        const size_t target; // target qubit number

        explicit Z(size_t target);
        ~Z() override = default;
    };

} // gates

#endif //QSIMULATOR_Z_H
