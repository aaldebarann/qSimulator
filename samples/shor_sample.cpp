//
// Created by aleksei on 9/15/23.
//
#include <iostream>
#include "shor.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

void shor(int N, int bits) {
    steady_clock::time_point begin, end;
    begin = steady_clock::now();
    size_t res = shor_quantum(N, bits, false);
    end = steady_clock::now();
    cout << res << " is divider of "<< N << endl;
    cout <<"total elapsed time: " << duration_cast<milliseconds>(end - begin).count() << " ms" << endl;
}

int main() {
    shor(21, 5);
}
