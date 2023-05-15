//
// Created by Алексей on 15.05.2023.
//

#include <gtest.h>
#include "System.h"

TEST(Gates, correct_cnot) {
    Matrix expected{8};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            expected(i, j) = 0;
        }
    }
    expected(0, 0) = 1;
    expected(1, 5) = 1;
    expected(2, 2) = 1;
    expected(3, 7) = 1;
    expected(4, 4) = 1;
    expected(5, 1) = 1;
    expected(6, 6) = 1;
    expected(7, 3) = 1;

    Matrix actual = System::CNOT(0, 2, 3);

    EXPECT_EQ(expected, actual);
}

