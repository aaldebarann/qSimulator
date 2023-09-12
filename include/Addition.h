//
// Created by Алексей on 14.07.2023.
//

#ifndef QSIMULATOR_ADDITION_H
#define QSIMULATOR_ADDITION_H

#include "System.h"
#include "Circuit.h"
#include <chrono>
#include <iostream>

unsigned classicalAdd(unsigned a, unsigned b, size_t bits) {
    std::cout << "begin" << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;

    if(bits > 4)
        throw std::out_of_range("classical addition can be executed with no more than 4 bits");
    System s(3*bits + 1);
    // кодируем слагаемые в состоянии системы
    end = std::chrono::steady_clock::now();
    std::cout << "1" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;

    Circuit* init = new Circuit(3*bits + 1);
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(3*i + 1);
        a = a >> 1;
        if(b % 2 == 1)
            init->x(3*i + 2);
        b = b >> 1;
    }
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "2" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;

    s.apply(*init);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "3" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
    delete init;
    // применяем схему классического сложения
    Circuit* circ = new Circuit(3*bits + 1);
    circ->add(bits);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "4" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
    s.apply(*circ);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "5" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;    delete circ;
    // измеряем состояние системы
    unsigned res = s.measure();
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "6" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for(int i = 0; i < bits; i++) {
        res = res >> 2;
        sum += (res % 2) << i;
        res = res >> 1;
    }
    sum += (res % 2) << bits;

    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "7" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
    return sum;
}
unsigned quantumAdd(unsigned a, unsigned b, size_t bits, bool approximate = false) {
    std::cout << "begin" << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;
    if(bits > 7)
        throw std::out_of_range("quantum addition can be executed with no more than 7 bits");
    System s(2*bits);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2*bits);
    end = std::chrono::steady_clock::now();
    std::cout << "1" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    for(int i = 0; i < bits; i++) {
        if(a % 2 == 1)
            init->x(2*bits - 1 -  i);
        a /= 2;
        if(b % 2 == 1)
            init->x(bits - 1 - i);
        b /= 2;
    }
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "2" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    s.apply(*init);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "3" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2*bits);
    // к слагаемому a необходимо применить КПФ
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "4" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    circ->qft(bits, bits + bits);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "4.1" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    s.apply(*circ);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "5" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    delete circ;
    Circuit* circ1 = new Circuit(2*bits);
    circ1->qadd(0, bits);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "6" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    s.apply(*circ1);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "7" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    delete circ1;
    // чтобы получить результат, необходимо обратное КПФ
    Circuit* circ2 = new Circuit(2*bits);
    circ2->iqft(bits, bits + bits);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "8" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    s.apply(*circ2);
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "9" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    delete circ2;
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
    begin = end;
    end = std::chrono::steady_clock::now();
    std::cout << "11" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milliseconds"<< std::endl;
    return sum;
}

#endif //QSIMULATOR_ADDITION_H
