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

// system measure
size_t System::measure() const {
    double r = (double)std::rand() / RAND_MAX;
    double sum = 0;
    for(int j = 0; j < state.size(); j++) {
        sum += std::abs(state[j].real()*state[j].real());
        sum += std::abs(state[j].imag()*state[j].imag());
        if(r < sum)
            return j;
    }
    return state.size() - 1;
}
// single qubit measure
vector<Complex> System::measure(size_t target) {
    double amplitude0 = 0;
    size_t n = state.size();
    for(int i = 0; i < n; i++) {
        if ((i & (1 << target)) == 0) {
            amplitude0 += state[i].real()*state[i].real();
            amplitude0 += state[i].imag()*state[i].imag();
        }
    }
    double r = (double)std::rand() / RAND_MAX;
    if(r < amplitude0) {
        // target qubit is in state |0>
        for(int i = 0; i < n; i++) {
            if ((i & (1 << target)) != 0) {
                state[i] = 0;
            }
        }
    } else {
        // target qubit is in state |1>
        for(int i = 0; i < n; i++) {
            if ((i & (1 << target)) == 0) {
                state[i] = 0;
            }
        }
    }
    // normalization
    double norm = 0;
    for(int i = 0; i < n; i++) {
        norm += state[i].real() * state[i].real();
        norm += state[i].imag() * state[i].imag();
    }
    norm = std::sqrt(norm);
    for(int i = 0; i < n; i++) {
        state[i] /= norm;
    }
    return state;
}

void System::apply(Circuit &circ) {
    for(Matrix& m: circ.getMatrices()) {
        state = m * state;
    }
}

std::map<int, int> System::measure(size_t t) const {
    std::map<int, int> m;
    for(int i = 0; i < t; i++) {
        int res = measure();
        auto x = m.find(res);
        if(x != m.end())
            x->second++;
        else
            m.insert({res, 1});
    }
    return m;
}
