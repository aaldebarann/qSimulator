//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_CNOT_H
#define QSIMULATOR_CNOT_H

#include "Gate.h"

namespace gates {

    class CNot: public Gate {
    public:
        const size_t target; // target qubit number
        const size_t control; // control qubit number

        CNot(size_t control, size_t target);
        ~CNot() override = default;

        Matrix getMatrix(size_t systemSize) override;
    };

} // gates

#endif //QSIMULATOR_CNOT_H
