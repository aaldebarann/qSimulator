//
// Created by Алексей on 15.05.2023.
//

#ifndef QSIMULATOR_SYSTEM_H
#define QSIMULATOR_SYSTEM_H

#include "Matrix.h"
#include "Circuit.h"


class System {

    vector<Complex> state;
public:
    const size_t size; // number of qubits

    explicit System(size_t size);
    System(vector<Complex>& state);

    vector<Complex> getState() const {
        return state;
    } // returns current state

    void apply(Circuit& circ); // применение схемы к системе

    size_t measure() const; // system measure
    vector<Complex> measure(size_t target); // system measure
};


#endif //QSIMULATOR_SYSTEM_H
