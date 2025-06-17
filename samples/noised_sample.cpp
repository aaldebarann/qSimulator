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

const size_t SHOTS = 1024;

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
    expectation /= SHOTS;
    return expectation;
}
double getZII(map<size_t, size_t> prob) {
    double expectation = 0.0;
    int num_qubits = 3;
    for (auto p: prob) {
        std::bitset<3> state(p.first);
        std::string bits = state.to_string();
        char first_qubit = bits[0]; // для IZI, второй кубит (Z) имеет индекс 1
        double eigenvalue = (first_qubit == '0') ? 1.0 : -1.0;
        expectation += p.second * eigenvalue;
    }
    expectation /= SHOTS;
    return expectation;
}
double getZZI(map<size_t, size_t> prob) {
    double expectation = 0.0;
    int num_qubits = 3;
    for (auto p: prob) {
        std::bitset<3> state(p.first);
        std::string bits = state.to_string();
        // Собственное значение зависит от первых двух кубитов (биты 'a' и 'b' в |abc>)
        char first_qubit = bits[0];  // Первый кубит (индекс 0)
        char second_qubit = bits[1]; // Второй кубит (индекс 1)
        double eigenvalue = ((first_qubit == '0') ? 1.0 : -1.0) * ((second_qubit == '0') ? 1.0 : -1.0);

        expectation += p.second * eigenvalue;
    }
    expectation /= SHOTS;
    return expectation;
}
double getZZZ(map<size_t, size_t> prob) {
    double expectation = 0.0;
    int num_qubits = 3;
    for (auto p: prob) {
        std::bitset<3> state(p.first);
        std::string bits = state.to_string();
        // Вычисляем собственное значение: (-1)^(число '1' в битовой строке)
        int parity = 0; // Чётность числа единиц
        for (char bit : bits) {
            if (bit == '1') parity++;
        }
        double eigenvalue = (parity % 2 == 0) ? 1.0 : -1.0;
        expectation += p.second * eigenvalue;
    }
    expectation /= SHOTS;
    return expectation;
}

double random_nums[] = {1.586115927180317, 2.017550251813147, 0.41758143704799666, 2.7971155931632667, 1.3363256458416872, 2.1993654562569205, 1.4274991801122212, 1.7053551031242211, 1.62834526362432, 1.6655868699744207, 2.85999492679127, 1.61442549501624, 2.14247050664778, 0.753583534079136, 2.64810021980059};


int main() {
    // при размере системы size=27 требуется порядка 10^8 операций
    // ожидаемое время исполнения одного гейта: 100 ms - 1000 ms
    // помним, что код измеряет время выполнения 10-ти базовых операций
    double gamma = 0.005441464;
    const size_t MAX_DEPTH = 200;
    for(int depth = 0; depth < MAX_DEPTH; depth ++) {
        std::map<size_t, size_t> m;
        for(int i = 0; i < SHOTS; i++) {
            StateVector s{6};
            for(int d = 0; d < depth; d++) {
                s.ru(random_nums[0], random_nums[5], random_nums[10], 3);
                s.ru(random_nums[1], random_nums[6], random_nums[11], 4);
                s.ru(random_nums[2], random_nums[7], random_nums[12], 5);
                s.ampDamp(gamma);
            }
            for(int d = 0; d < depth; d++) {
                s.ru(-random_nums[0], -random_nums[10], -random_nums[5], 3);
                s.ru(-random_nums[1], -random_nums[11], -random_nums[6], 4);
                s.ru(-random_nums[2], -random_nums[12], -random_nums[7], 5);
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
        std::cout << getIZI(m) << std::endl;
    }
}