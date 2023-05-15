//
// Created by Алексей on 15.05.2023.
//

#include "System.h"

System::System(size_t sz): size(sz) {
    state.resize((size_t)pow(2, size));
    for(Complex z: state)
        z = 0;
}
