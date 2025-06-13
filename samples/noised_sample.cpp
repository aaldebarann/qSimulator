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

double getIZI(map<size_t, size_t> prob) {
    double expectation = 0.0;
    int num_qubits = 3;
    for (auto p: prob) {
        std::bitset<3> state(p.first);
        std::string bits = state.to_string();
        char second_qubit = bits[1]; // для IZI, второй кубит (Z) имеет индекс 1
        double eigenvalue = (second_qubit == '0') ? 1.0 : -1.0;
        expectation += p.second * eigenvalue;
    }
    expectation /= 1024.0;
    return expectation;
}


int main() {
    // при размере системы size=27 требуется порядка 10^8 операций
    // ожидаемое время исполнения одного гейта: 100 ms - 1000 ms
    // помним, что код измеряет время выполнения 10-ти базовых операций
    double gamma = 0.2;
    const size_t MAX_DEPTH = 50;
    for(int depth = 0; depth < MAX_DEPTH; depth ++) {
        std::map<size_t, size_t> m;
        for(int i = 0; i < 1000; i++) {
            StateVector s{6};
            for(int d = 0; d < depth; d++) {
                s.ru(1.1, 2.2, 0.3, 3);
                s.ru(2.1, 2.9, 3.1, 4);
                s.ru(0.5789, 1.9, 2.3456, 5);
                s.ampDamp(gamma);
            }
            for(int d = 0; d < depth; d++) {
                s.ru(-1.1, -0.3, -2.2, 3);
                s.ru(-2.1, -3.1, -2.9, 4);
                s.ru(-0.5789, -2.3456, -1.9, 5);
                s.ampDamp(gamma);
            }
            // s.print();
            size_t t = s.measure();
            t = t / 8;
            if(m.count(t) > 0) {
                m[t]++;
            } else {
                m.insert({t, 1});
            }
        }
        // for (const auto& [key, value] : m)
        //     std::cout << '[' << std::bitset<3>(key) << "] = " << value << "\n";
        std::cout << "IZI (" << depth << ") = " << getIZI(m) << std::endl;
    }
}