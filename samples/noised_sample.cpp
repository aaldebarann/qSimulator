//
// Created by aleksei on 9/15/23.
// Измерение производительности базовых гейтов (в реализации без матриц гейтов)
#include <iostream>
#include <chrono>
#include <bitset>
#include "StateVector.h"
using namespace std;
using namespace std::chrono;

int main() {
    // при размере системы size=27 требуется порядка 10^8 операций
    // ожидаемое время исполнения одного гейта: 100 ms - 1000 ms
    // помним, что код измеряет время выполнения 10-ти базовых операций

    StateVector s{4};

    double gamma = 0.9;
    s.h(0);
    s.h(1);
    s.z(0);
    s.ampDamp(gamma);
    for(int i = 0; i < 100; i++) {
        cout << "measure " << i << ":   " << std::bitset<2>(s.measure()) << endl;
    }
}