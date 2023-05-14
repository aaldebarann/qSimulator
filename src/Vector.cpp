//
// Created by Алексей on 14.05.2023.
//

#include "Vector.h"

Vector::Vector(size_t sz): size(sz) {
    pMem = new std::complex<float>[size];
}
Vector::~Vector() {
    delete[] pMem;
}

complex<float>& Vector::operator[](size_t i) {
    return pMem[i];
}

Vector::Vector(size_t size, std::complex<float> value): Vector(size) {
    for(int i = 0; i < size; i++)
        pMem[i] = value;
}
