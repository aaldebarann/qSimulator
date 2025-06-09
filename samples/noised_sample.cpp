//
// Created by aleksei on 9/15/23.
// Измерение производительности базовых гейтов (в реализации без матриц гейтов)
#include <iostream>
#include <chrono>
#include <bitset>
#include "StateVector.h"
using namespace std;
using namespace std::chrono;

void baseOperations(StateVector* s) {
    // к системе применяется набор базовых гейтов
    s->h(0);
    s->x(1);
}

int main() {
    size_t size = 2;
    // при размере системы size=27 требуется порядка 10^8 операций
    // ожидаемое время исполнения одного гейта: 100 ms - 1000 ms
    // помним, что код измеряет время выполнения 10-ти базовых операций

    steady_clock::time_point begin, end;
    StateVector* s = new StateVector(size);
    begin = steady_clock::now();
    baseOperations(s);
    end = steady_clock::now();
    cout <<"total elapsed time: " << duration_cast<milliseconds>(end - begin).count() << " ms" << endl;
    for(int i = 0; i < 100; i++) {
        cout << "measure " << i << ":   " << std::bitset<2>(s->measure()) << endl;
    }
    delete s;
}