//
// Created by aleksei on 28.05.23.
//

#ifndef QSIMULATOR_SINGLEQUBITGATE_H
#define QSIMULATOR_SINGLEQUBITGATE_H

#include "gates/Gate.h"

namespace gates {
    class SingleQubitGate : public Gate {
    protected:
        virtual Matrix matrix() = 0; // gate matrix;
    public:
        const size_t target;

        explicit SingleQubitGate(size_t target);
        ~SingleQubitGate() override = default;

        Matrix getMatrix(size_t systemSize) override;
    };
}


#endif //QSIMULATOR_SINGLEQUBITGATE_H
