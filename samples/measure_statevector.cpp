//
// Created by aleksei on 9/15/23.
// Измерение производительности базовых гейтов (в реализации без матриц гейтов)
#include <iostream>
#include "StateVector.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

void baseOperations(StateVector* s) {
    // к системе применяется набор базовых гейтов
    s->i(s->size - 2);
    s->x(s->size - 3);
    s->y(s->size - 4);
    s->z(s->size - 2);
    s->h(s->size - 3);
    s->p(0.3 ,s->size - 4);
    s->cnot(1, s->size - 2);
    s->p(0.3 ,s->size - 3);
    s->cp(0.3 ,s->size - 3, s->size - 4);
    s->ccp(0.3 ,s->size - 2, s->size - 3, s->size - 4);
}

int main() {
    size_t size = 25;
    // при размере системы size=27 требуется порядка 10^8 операций
    // ожидаемое время исполнения одного гейта: 100 ms - 1000 ms
    // помним, что код измеряет время выполнения 10-ти базовых операций

    steady_clock::time_point begin, end;
    StateVector* s = new StateVector(size);
    begin = steady_clock::now();
    baseOperations(s);
    end = steady_clock::now();
    cout <<"total elapsed time: " << duration_cast<milliseconds>(end - begin).count() << " ms" << endl;
    delete s;
}