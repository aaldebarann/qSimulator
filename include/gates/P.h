//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_P_H
#define QSIMULATOR_P_H

#include "SingleQubitGate.h"

namespace gates {
    // Phase shift gate
    class P: public SingleQubitGate {
    private:
        Matrix matrix() override; // matrix of H gate
    public:
        const size_t target; // target qubit number
        const Complex phi; // phase shift

        P(size_t target, Complex phi);
        ~P() override = default;
    };

} // gates

#endif //QSIMULATOR_P_H
