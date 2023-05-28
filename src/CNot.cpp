//
// Created by aleksei on 28.05.23.
//

#include "gates/CNot.h"

namespace gates {
    CNot::CNot(size_t control, size_t target) : target(target), control(control) {}
    // !!!

    Matrix CNot::getMatrix(size_t systemSize) {
        if(control >= systemSize)
            throw std::out_of_range("control qubit number is out of range");
        if(target >= systemSize)
            throw std::out_of_range("target qubit number is out of range");
        if(control == target)
            throw std::invalid_argument("target and control can't be the same qubit");


        Matrix m1{2, 0}, m2{2, 0};
        m1(0, 0) = m2(1, 1) = 1;
        Matrix id = I();
        Matrix x = X();

        Matrix res1{1, 1};
        for(int k = 0; k < systemSize; k++) {
            if(k == control)
                res1 = res1.kron(m1);
            else
                res1 = res1.kron(id);
        }
        Matrix res2{1, 1};
        for(int k = 0; k < systemSize; k++) {
            if(k == control)
                res2 = res2.kron(m2);
            else if(k == target)
                res2 = res2.kron(x);
            else
                res2 = res2.kron(id);
        }
        res1 += res2;
        return res1;
    }
} // gates