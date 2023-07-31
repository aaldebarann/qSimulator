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
    Circuit* init = new Circuit(3*bits + 1);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(3*i + 1);
        a = a >> 1;
        if(b % 2 == 1)
            init->x(3*i + 2);
        b = b >> 1;
    }
    s.apply(*init);
    // применяем схему классического сложения
    Circuit* circ = new Circuit(3*bits + 1);
    circ->add_classic(bits);
    s.apply(*circ);
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
unsigned quantumAdd(unsigned a, unsigned b, size_t bits) {
    if(bits > 7)
        throw std::out_of_range("quantum addition can be executed with no more than 7 bits");
    System s(2*bits);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2*bits);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(2*bits - 1 -  i);
        a = a >> 1;
        if(b % 2 == 1)
            init->x(bits - 1 - i);
        b = b >> 1;
    }
    // к слагаемому a необходимо применить КПФ
    init->qft(bits, bits + bits);
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2*bits);
    circ->add_quantum(bits);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits);
    s.apply(*circ);
    delete circ;
    // измеряем состояние системы
    unsigned res = s.measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    res = res >> bits;
    for(int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    return sum;
}

#endif //QSIMULATOR_ADDITION_H
