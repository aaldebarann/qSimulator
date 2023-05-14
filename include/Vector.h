//
// Created by Алексей on 14.05.2023.
//

#ifndef QSIMULATOR_VECTOR_H
#define QSIMULATOR_VECTOR_H

#include <complex>
using std::complex;


class Vector {
    complex<float>* pMem;
public:
    const size_t size;
    Vector(size_t size);
    Vector(size_t size, std::complex<float> value);
    ~Vector();

    complex<float>& operator[](size_t i);
    bool operator==(Vector& v) {
        if(size != v.size)
            return false;
        for(int i = 0; i < size; i++) {
            if((*this)[i] != v[i])
                return false;
        }
        return true;
    }

};


#endif //QSIMULATOR_VECTOR_H
