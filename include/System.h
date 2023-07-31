//
// Created by Алексей on 15.05.2023.
//

#ifndef QSIMULATOR_SYSTEM_H
#define QSIMULATOR_SYSTEM_H

#include "Matrix.h"
#include "Circuit.h"
#include <map>

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

    // system measure
    size_t measure() const; // returns result of system measure (doesn't change system state)
    std::map<int, int> measure(size_t t) const;
    vector<Complex> measure(size_t target); // returns state after single-qubit measure (changes system state)
};


#endif //QSIMULATOR_SYSTEM_H
