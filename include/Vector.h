//
// Created by Алексей on 14.05.2023.
//

#ifndef QSIMULATOR_VECTOR_H
#define QSIMULATOR_VECTOR_H

#include <complex>
#include <vector>
using std::complex;


class Vector {
    complex<float>* pMem;
public:
    const size_t size;
    Vector(size_t size);
    Vector(size_t size, std::complex<float> value);
    Vector(Vector& v);
    ~Vector();

    complex<float>& operator[](size_t i);
    Vector& operator=(Vector v);
};


#endif //QSIMULATOR_VECTOR_H
