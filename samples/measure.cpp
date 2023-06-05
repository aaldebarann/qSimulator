//
// Created by aleksei on 05.06.23.
//
#include <iostream>
#include <System.h>
#include <fstream>

using namespace std;

int main() {
    System s{3};

    Circuit circ(3);
    circ.x(0);
    circ.h(1);
    circ.p(-M_PI / 4, 1 );
    circ.cnot(0, 1);
    circ.p(M_PI / 2, 1);
    circ.cnot(0, 1);
    s.apply(circ);
    /*
    // measure
    for(int i = 0; i < 100; i++) {
        cout << s.measure() << endl;
    }
    */
    // single qubit measure
    for(int i = 0; i < 100; i++) {
        System s1(s);
        s1.measure(0);
        s1.measure(1);
        vector<Complex> state = s1.measure(2);
        for(int j = 0; j < state.size(); j++) {
            Complex z = state[j];
            // cout << z;
            if(z.real()*z.real()  + z.imag()*z.imag() > 0.9999) {
                cout << j << endl;
            }
        }
        // cout << endl;
    }
}