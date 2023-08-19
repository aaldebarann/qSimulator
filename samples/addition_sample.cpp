//
// Created by Алексей on 30.07.2023.
//

#include <iostream>
#include "System.h"
#include "Addition.h"
#include <chrono>
using namespace std;

void test_classic(size_t a, size_t b, size_t bits) {
    cout << "classical add"<<endl;
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res = classicalAdd(a, b, bits);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "total elapsed time: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
}
void test_quantum(size_t a, size_t b, size_t bits) {
    cout << "quantum add"<<endl;
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res = quantumAdd(a, b, bits, false);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "total elapsed time: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
}

int main() {
    /*test_quantum(0, 0, 1);
    test_quantum(0, 1, 1);
    test_quantum(1, 0, 1);
    test_quantum(1, 1, 1);
    test_quantum(1, 2, 2);
    test_quantum(2, 1, 2);
    test_quantum(2, 0, 2);
    test_quantum(0, 2, 2);
    test_quantum(2, 4, 3);
    */
    //test_quantum(31, 29, 5);

/*
    test_classic(0, 0, 1);
    test_classic(0, 1, 1);
    test_classic(1, 0, 1);
    test_classic(1, 1, 2);
    test_classic(1, 2, 2);
    test_classic(2, 1, 2);
    test_classic(2, 0, 2);
    test_classic(0, 2, 2);
    test_classic(2, 4, 3);
    */
    test_classic(6, 7, 3);
}