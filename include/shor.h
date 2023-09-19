//
// Created by Aleksei on 08.08.2023.
//

#ifndef QSIMULATOR_SHOR_H
#define QSIMULATOR_SHOR_H

#include <cstdlib>
#include <cmath>
#include <cstdint>
#include "StateVector.h"

using std::abs;
using std::rand;

int findOrder(uint32_t x, uint32_t module) {
    int r = 1;
    uint64_t tmp = x % module;
    while(tmp != 1) {
        tmp *= x;
        tmp %= module;
        r++;
    }
    return r;
}

int64_t gcd(int64_t a, int64_t b) {
    a = abs(a);
    b = abs(b);
    if(b == 0) {
        return a;
    } else {
        int64_t r = a % b;
        while(r != 0) {
            a = b;
            b = r;
            r = a % b;
        }
        return b;
    }
} // возвращает НОД (a, b)

uint32_t modPow(uint32_t base, uint32_t exp, uint32_t m) {
    if(exp == 0) {
        return 1;
    }
    uint64_t tmp = modPow(base, exp/2, m);
    if(exp % 2 == 0) {
        return (tmp * tmp) % m;
    } else {
        return ((tmp * tmp) % m ) * base % m;
    }
} // returns (base ^ exp) mod m

uint32_t perfectPower(uint32_t n) {
    for(uint32_t q = 2; q < 32 && q < n; q++) {
        // check if q-th root of n is integer
        // with binary search
        uint32_t pMin = 2, pMax = n, p;
        while(pMin <= pMax) {
            p = (pMin + pMax) / 2;
            double tmp = pow((double) p, (double) q);
            if (tmp == n) {
                return p;
            } else if (tmp < n) {
                // p must be bigger
                pMin = p + 1;
            } else {
                // p must be smaller
                pMax = p - 1;
            }
        }
    }
    return 0;
} // returns the factor p where n = p^q or 0 if p doesn't exist

uint32_t quantumOrderFinding(uint32_t x, uint32_t module, uint32_t bits, bool approximate = false) {
    StateVector* s = new StateVector(4*bits + 2);

    for(int i = 0; i < 2*bits; i++) {
        s->h(i);
    }
    for(int i = 0; i < 2*bits; i++) {
        // tmp = a ^ (2 ^ i)
        // taking by module to prevent overflow
        size_t tmp = modPow(x, (1 << i), module);
        s->u(tmp, module, 2*bits - 1 - i, 2*bits, bits, approximate);
    }
    s->qft(0, 2*bits, approximate);
    size_t r = s->measure();
    return (r >> 2*bits);
}

uint32_t shor_classic(uint32_t N) {
    if(N % 2 == 0)
        return 2;
    uint32_t tmp = perfectPower(N);
    if(tmp != 0)
        return tmp;
    uint32_t x, y, r;
    while (true) {
        x = rand() % (N - 1) + 1;
        if (gcd(x, N) > 1)
            return gcd(x, N);
        r = findOrder(x, N);
        y = gcd(N, modPow(x, r / 2, N) + 1);
        if (N % y == 0 && y != 1 && y != N)
            return y;
        y = gcd(N, modPow(x, r / 2, N) - 1);
        if (N % y == 0 && y != 1 && y != N)
            return y;
    }
}
uint32_t shor_quantum(uint32_t N, uint32_t bits, uint32_t approximate = false) {
    if(N % 2 == 0)
        return 2;
    uint32_t tmp = perfectPower(N);
    if(tmp != 0)
        return tmp;
    uint32_t x, y, r;
    while (true) {
        x = rand() % (N - 1) + 1;
        if (gcd(x, N) > 1)
            return gcd(x, N);
        r = quantumOrderFinding(x, N, bits, approximate);
        y = gcd(N, modPow(x, r / 2, N) + 1);
        if (N % y == 0 && y != 1 && y != N)
            return y;
        y = gcd(N, modPow(x, r / 2, N) - 1);
        if (N % y == 0 && y != 1 && y != N)
            return y;
    }
}

#endif //QSIMULATOR_SHOR_H