//
// Created by aleksei on 05.06.23.
//
#include <iostream>
#include <System.h>
#include <fstream>

using namespace std;

int main() {
    vector<Circuit> v;

    Circuit circ1(3);
    circ1.x(1);
    circ1.h(0);
    circ1.z(1);
    circ1.cnot(0, 1);
    circ1.x(0);
    circ1.cnot(2, 1);
    circ1.h(0);
    circ1.z(1);
    v.push_back(circ1);

    Circuit circ2(3);
    circ2.h(0);
    circ2.cnot(0, 1);
    v.push_back(circ2);

    Circuit circ3(3);
    circ3.h(0);
    circ3.x(1);
    circ3.cnot(1, 0);
    v.push_back(circ3);

    Circuit circ4(3);
    circ4.h(0);
    circ4.x(1);
    circ4.cnot(1, 0);
    circ4.x(2);
    circ4.z(1);
    v.push_back(circ4);

    Circuit circ5(3);
    circ5.h(0);
    circ5.cnot(0, 2);
    v.push_back(circ5);

    Circuit circ6(3);
    circ6.h(0);
    circ6.x(2);
    circ6.cnot(0, 2);
    v.push_back(circ6);

    Circuit circ7(3);
    circ7.h(0);
    circ7.x(2);
    circ7.cnot(0, 2);
    circ7.p(M_PI / 2, 2);
    v.push_back(circ7);

    Circuit circ8(3);
    circ8.p(-M_PI / 4, 1);
    circ8.cnot(0, 1);
    circ8.p(M_PI / 4, 1);
    circ8.cnot(0, 1);
    v.push_back(circ8);

    Circuit circ9(3);
    circ9.x(0);
    circ9.h(1);
    circ9.p(-M_PI / 4, 1 );
    circ9.cnot(0, 1);
    circ9.p(M_PI / 2, 1);
    circ9.cnot(0, 1);
    v.push_back(circ9);
    for(Circuit circ: v) {
        System s(3);
        s.apply(circ);
        // system measure
        int a[8] = {};
        cout << "system measure" << endl;
        for(int i = 0; i < 100; i++) {
            a[s.measure()]++;
        }
        for(int i: a) {
            cout << i << ' ';
        }
        cout << endl;
        // single qubit measure
        cout << "single qubit measure" << endl;
        int b[8] = {};
        for(int i = 0; i < 100; i++) {
            System s1(s);
            s1.measure(0);
            s1.measure(1);
            vector<Complex> state = s1.measure(2);
            for(int j = 0; j < state.size(); j++) {
                Complex z = state[j];
                // cout << z;
                if(z.real()*z.real()  + z.imag()*z.imag() > 0.9999) {
                    b[j]++;
                }
            }
            // cout << endl;
        }
        for(int i: b) {
            cout << i << ' ';
        }
        cout << endl;
        cout << endl;
    }

}