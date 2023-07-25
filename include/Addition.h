//
// Created by Алексей on 14.07.2023.
//

#ifndef QSIMULATOR_ADDITION_H
#define QSIMULATOR_ADDITION_H

#include "System.h"
#include "Circuit.h"

unsigned classicalAdd(unsigned a, unsigned b, size_t bits) {
    if(bits > 4)
        throw std::out_of_range("classical addition can be executed with no more than 4 bits");
    System s(3*bits + 1);
    // кодируем слагаемые в состоянии системы
    Circuit init(3*bits + 1);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init.x(3*i + 1);
        a = a >> 1;
        if(b % 2 == 1)
            init.x(3*i + 2);
        b = b >> 1;
    }
    s.apply(init);
    // применяем схему классического сложения
    Circuit circ(3*bits + 1);
    circ.add_classic(bits);
    s.apply(circ);
    // измеряем состояние системы
    unsigned res = s.measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for(int i = 0; i < bits; i++) {
        res = res >> 2;
        sum += (res % 2) << i;
        res = res >> 1;
    }
    sum += (res % 2) << bits;
    return sum;
}

#endif //QSIMULATOR_ADDITION_H
