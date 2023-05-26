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

    vector<Complex> getState() {
        return state;
    } // returns current state
    void apply(vector<Matrix>& v) {
        // составляем итоговую матрицу преобразования
        Matrix m = v[0];
        for(int i = 1; i < v.size(); i++)
            m = m.kron(v[i]);
        state = m*state;
    }
};


#endif //QSIMULATOR_SYSTEM_H
