//
// Created by Алексей on 14.07.2023.
//

#ifndef QSIMULATOR_ADDITION_H
#define QSIMULATOR_ADDITION_H

#include "System.h"
#include "Circuit.h"
#include "StateVector.h"
#include <iostream>

/*
 * addition with matrices
 *
unsigned classicalAdd(unsigned a, unsigned b, size_t bits) {

    if(bits > 6)
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
    delete init;
    // применяем схему классического сложения
    Circuit* circ = new Circuit(3*bits + 1);
    circ->add(bits);
    s.apply(*circ);
    delete circ;
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
unsigned quantumAdd(unsigned a, unsigned b, size_t bits, bool approximate = false) {
    if(bits > 7)
        throw std::out_of_range("quantum addition can be executed with no more than 7 bits");
    System s(2*bits);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2*bits);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(2*bits - 1 -  i);
        a /= 2;
        if(b % 2 == 1)
            init->x(bits - 1 - i);
        b /= 2;
    }
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2*bits);
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, approximate);
    // схема квантового сложения
    circ->qadd(0, bits, approximate);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, approximate);
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
 */

unsigned classicalAdd(unsigned a, unsigned b, size_t bits) {
      StateVector* s = new StateVector(3*bits + 1);
    // кодируем слагаемые в состоянии системы
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            s->x(3*i + 1);
        a = a >> 1;
        if(b % 2 == 1)
            s->x(3*i + 2);
        b = b >> 1;
    }
    // применяем схему классического сложения
    s->add(bits);
    // измеряем состояние системы
    unsigned res = s->measure();
    delete s;
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
unsigned quantumAdd(unsigned a, unsigned b, size_t bits, bool approximate = false) {
    StateVector* s = new StateVector(bits);
    // кодируем слагаемые в состоянии системы
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            s->x(bits - 1 -  i);
        a /= 2;
    }
    // применяем схему квантового сложения
    // к слагаемому a необходимо применить КПФ
    s->qft(0, bits, approximate);
    // схема квантового сложения
    s->qadd(b, 0, bits, approximate);
    // чтобы получить результат, необходимо обратное КПФ
    s->iqft(0, bits, approximate);
    // измеряем состояние системы
    unsigned res = s->measure();
    delete s;
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for(int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    return sum;
}
/*
unsigned quantumAdd_1c(unsigned a, unsigned b, size_t bits, bool approximate = false) {
    if(bits > 7)
        throw std::out_of_range("quantum addition can be executed with no more than 7 bits");
    System s(2*bits + 1);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2*bits + 1);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(2*bits - 1 -  i);
        a /= 2;
        if(b % 2 == 1)
            init->x(bits - 1 - i);
        b /= 2;
    }
    init->x(2*bits);
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2*bits + 1);
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, approximate);
    // схема квантового сложения
    circ->qadd_1c(2*bits, 0, bits, approximate);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, approximate);
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
unsigned quantumAdd_2c(unsigned a, unsigned b, size_t bits, bool approximate = false) {
    if(bits > 7)
        throw std::out_of_range("quantum addition can be executed with no more than 7 bits");
    System s(2*bits + 2);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2*bits + 2);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(2*bits - 1 -  i);
        a /= 2;
        if(b % 2 == 1)
            init->x(bits - 1 - i);
        b /= 2;
    }
    init->x(2*bits);
    init->x(2*bits + 1);
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2*bits + 2);
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, approximate);
    // схема квантового сложения
    circ->qadd_2c(2*bits, 2*bits + 1, 0, bits, approximate);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, approximate);
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
*/
#endif //QSIMULATOR_ADDITION_H