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
