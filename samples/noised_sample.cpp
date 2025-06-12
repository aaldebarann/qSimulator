//
// Created by aleksei on 9/15/23.
// Измерение производительности базовых гейтов (в реализации без матриц гейтов)
#include <iostream>
#include <chrono>
#include <bitset>
#include <map>
#include "StateVector.h"
using namespace std;
using namespace std::chrono;

// void print_insertion_status(It it, bool success)
// {
//     std::cout << "Insertion of " << it->first
//               << (success ? " succeeded\n" : " failed\n");
// }

int main() {
    // при размере системы size=27 требуется порядка 10^8 операций
    // ожидаемое время исполнения одного гейта: 100 ms - 1000 ms
    // помним, что код измеряет время выполнения 10-ти базовых операций


    double gamma = 0.8;

    std::map<size_t, int> m;
    for(int i = 0; i < 1000; i++) {
        StateVector s{6};
        s.h(3);
        s.h(4);
        s.h(5);
        s.ampDamp(gamma);
        s.print();
        size_t t = s.measure();
        t = t / 8;
        if(m.count(t) > 0) {
            m[t]++;
        } else {
            m.insert({t, 1});
        }
    }
    for (const auto& [key, value] : m)
        std::cout << '[' << std::bitset<3>(key) << "] = " << value << "\n";
}