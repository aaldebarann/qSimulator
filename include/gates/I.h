//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_I_H
#define QSIMULATOR_I_H

#include "SingleQubitGate.h"

namespace gates {
    // Identity gate
    class I: public SingleQubitGate {
    private:
        Matrix matrix() override; // matrix of H gate
    public:
        const size_t target; // target qubit number

        explicit I(size_t target);
        ~I() override = default;
    };

} // gates

#endif //QSIMULATOR_I_H
