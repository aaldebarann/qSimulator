//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_H_H
#define QSIMULATOR_H_H

#include "SingleQubitGate.h"

namespace gates {

    class H: public SingleQubitGate {
    private:
        Matrix matrix() override; // matrix of H gate
    public:
        const size_t target; // target qubit number

        explicit H(size_t target);
        ~H() override = default;
    };

} // gates

#endif //QSIMULATOR_H_H
