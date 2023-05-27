//
// Created by Алексей on 15.05.2023.
//

#include "System.h"

System::System(size_t sz): size(sz) {
    state.resize((size_t)pow(2, size));
    for(Complex z: state)
        z = 0;
    state[0] = 1;
}

void System::apply(Matrix &m) {
    if(m.size() != (size_t)pow(2, this->size))
        throw std::invalid_argument("Matrix size doesn't match system size");
    state = m * state;
}

System::System(vector<Complex>& state): System(state.size()) {
    this->state = state;
}
