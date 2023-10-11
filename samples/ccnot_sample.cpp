//
// Created by Алексей on 13.07.2023.
//

#include <iostream>
#include <Gates.h>
#include "System.h"

using namespace std;

int main() {
    Matrix* m = CCNOT(0, 1, 2, 4);
    for(int i = 0;  i < m->size(); i++) {
        for(int j = 0; j < m->size(); j++) {
            cout << (*m)(i, j) << " ";
        }
        cout << endl;
    }
}