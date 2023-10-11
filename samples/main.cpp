//
// Created by aleksei on 28.05.23.
//
#include <iostream>
#include <System.h>
#include <chrono>
using namespace std;

int main() {
    size_t size = 14;
    cout << "system size: "<< size << endl;
    System s{size};
    Circuit* circ = new Circuit(size);
    // time measurements 
    chrono::steady_clock::time_point begin, end;
    // calculating the gate matrix
    begin = std::chrono::steady_clock::now();
    circ->h(8);
    end = std::chrono::steady_clock::now();
    cout << "calculating the gate matrix: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    // applying the circuit
    begin = std::chrono::steady_clock::now();
    s.apply(*circ);
    end = std::chrono::steady_clock::now();
    cout << "applying the circuit: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    
    // now system state is {1.0 / sqrt(2), 0, ... 0, 1.0 / sqrt(2), 0, ..., 0};
    // where non-zero elements are in places 0, 2^size
    for(int i = 0; i < 100; i++)
        cout << "Measure "<<i<<": "<<s.measure()<< endl;

}