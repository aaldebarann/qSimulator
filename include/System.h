//
// Created by Алексей on 15.05.2023.
//

#ifndef QSIMULATOR_SYSTEM_H
#define QSIMULATOR_SYSTEM_H

#include "Vector.h"
#include "Matrix.h"

class System {

    vector<Complex> state;
public:
    const size_t size; // qubit number

    explicit System(size_t size);

    static Matrix I() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        return matrix;
    } // Identity gate
    static Matrix X() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        matrix(0, 1) = matrix(1, 0) = 1;
        return matrix;
    } // NOT gate or Pauli-X
    static Matrix Y() {
        Matrix matrix(2);
        matrix(0, 0) = matrix(1, 1) = 0;
        complex<float> i(0, 1);
        matrix(0, 1) = -i;
        matrix(1, 0) = i;
        return matrix;
    } // Pauli-Y
    static Matrix Z() {
        Matrix matrix(2);
        matrix(0, 0) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        matrix(1, 1) = -1;
        return matrix;
    } // Pauli-Z
    static Matrix H() {
        Matrix matrix(2);
        float tmp = 1.0 / sqrt(2);
        matrix(0, 0) =  matrix(0, 1) = matrix(1, 0) = tmp;
        matrix(1, 1) = -tmp;
        return matrix;
    } // Hadamard
    static Matrix P(complex<float> phi) {
        Matrix matrix(2);
        complex<float> i(0, 1);
        matrix(0, 0) = 1;
        matrix(0, 1) = matrix(1, 0) = 0;
        matrix(1, 1) = std::exp(phi * i);
        return matrix;
    } // phase shift
    static Matrix CNOT(size_t i, size_t j, size_t qubit_number) {
        Matrix m1{2}, m2{2};
        m1(0, 0) = m2(1, 1) = 1;
        m1(0, 1) = m1(1, 0) = m1(1, 1) = 0;
        m2(0, 0) = m2(0, 1) = m2(1, 0) = 0;
        Matrix id = I();
        Matrix x = X();

        Matrix res1{1};
        res1(0, 0) = 1;
        for(int k = 0; k < qubit_number; k++) {
            if(k == i)
                res1 = res1.kron(m1);
            else
                res1 = res1.kron(id);
        }
        Matrix res2{1};
        res2(0, 0) = 1;
        for(int k = 0; k < qubit_number; k++) {
            if(k == i)
                res2 = res2.kron(m2);
            else if(k == j)
                res2 = res2.kron(x);
            else
                res2 = res2.kron(id);
        }
        return res1 += res2;
    }

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
