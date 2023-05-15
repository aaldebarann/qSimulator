//
// Created by Алексей on 15.05.2023.
//

#include "System.h"

System::System(size_t sz): size(sz) {
    state = new Vector((size_t)pow(2, size), 0);
}
System::~System() {
    delete state;
}
