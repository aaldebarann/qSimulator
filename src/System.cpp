//
// Created by Алексей on 15.05.2023.
//

#include "System.h"
#include <cstdlib>

System::System(size_t sz): size(sz) {
    state.resize((size_t)pow(2, size));
    for(Complex z: state)
        z = 0;
    state[0] = 1;
}

System::System(vector<Complex>& state): System(state.size()) {
    this->state = state;
}

void System::apply(Gate* g) {
    Matrix m = g->getMatrix(size);
    state = m * state;
}
void System::apply(const vector<Gate *>& gatesVector) {
    for(Gate* g: gatesVector) {
        Matrix m = g->getMatrix(size);
        state = m * state;
    }
}

size_t System::measure() const {
    double r = (double)std::rand() / RAND_MAX;
    double sum = 0;
    for(int j = 0; j < pow(2, (double)size); j++) {
        sum += std::abs((state[j]*state[j]).real());
        if(r < sum)
            return j;
    }
    return size - 1;
}
