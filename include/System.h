//
// Created by Алексей on 15.05.2023.
//

#ifndef QSIMULATOR_SYSTEM_H
#define QSIMULATOR_SYSTEM_H

#include "Matrix.h"

class System {

    vector<Complex> state;
public:
    const size_t size; // number of qubits

    explicit System(size_t size);
    System(vector<Complex>& state);

    vector<Complex> getState() {
        return state;
    } // returns current state
    void apply(Matrix& m); // применение матрицы к системе

};


#endif //QSIMULATOR_SYSTEM_H
