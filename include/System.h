//
// Created by Алексей on 15.05.2023.
//

#ifndef QSIMULATOR_SYSTEM_H
#define QSIMULATOR_SYSTEM_H

#include "Matrix.h"
#include "Gates.h"

class System {

    vector<Complex> state;
public:
    const size_t size; // number of qubits

    explicit System(size_t size);
    System(vector<Complex>& state);

    vector<Complex> getState() const {
        return state;
    } // returns current state
    void apply(Gate* g); // применение вентиля к системе
    void apply(const vector<Gate*>& gatesVector);

    size_t measure() const;
};


#endif //QSIMULATOR_SYSTEM_H
