//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_Y_H
#define QSIMULATOR_Y_H

#include "SingleQubitGate.h"

namespace gates {
    // Pauli-Y gate
    class Y: public SingleQubitGate {
    private:
        Matrix matrix() override; // matrix of H gate
    public:
        const size_t target; // target qubit number

        explicit Y(size_t target);
        ~Y() override = default;
    };

} // gates

#endif //QSIMULATOR_Y_H
