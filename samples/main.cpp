//
// Created by aleksei on 28.05.23.
//
#include <iostream>
#include <System.h>
#include <chrono>
using namespace std;

int main() {
    size_t size = 14;
    cout << "system size: " << size << endl;
    System s{size};
    Circuit *circ = new Circuit(size);
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    circ->h(0);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    s.apply(*circ);
    begin = end;
    end = std::chrono::steady_clock::now();
    cout << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    // now system state is {1.0 / sqrt(2), 0, ... 0, 1.0 / sqrt(2), 0, ..., 0};
    // where non-zero elements are in places 0, 2^size
    for (int i = 0; i < 10; i++)
        cout << "Measure " << i << ": " << s.measure() << endl;
}