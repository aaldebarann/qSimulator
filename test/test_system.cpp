//
// Created by Алексей on 15.05.2023.
//

#include <gtest.h>
#include "System.h"
#include "Gates.h"

TEST(System, can_create) {
    ASSERT_NO_THROW(System s(3));
}
TEST(System, can_get_state) {
    System s(3);
    ASSERT_NO_THROW(s.getState());
}
TEST(System, initial_state_is_zero) {
    System s(3);
    vector<Complex> expected{1, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(expected, s.getState());
}
TEST(System, identity_circuit) {
    System s1{3}, s2{3};
    vector<Matrix> step;
    for(int i = 0; i < 3; i++)
        step.push_back(I());
    s1.apply(step);
    EXPECT_EQ(s2.getState(), s1.getState());
}
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

    Matrix actual = CNOT(0, 2, 3);
    EXPECT_EQ(expected, actual);
}
TEST(System, circuit_s2) {
    System s{3};

    vector<Matrix> step1;
    step1.push_back(H());
    step1.push_back(I());
    step1.push_back(I());
    s.apply(step1);

    vector<Matrix> step2;
    step2.push_back(CNOT(0, 1, 3));
    s.apply(step2);

    vector<Complex> expected(8, 0);
    expected[0] = -0.5;
    expected[1] = -0.5;
    expected[2] = 0.5;
    expected[3] = -0.5;

    EXPECT_EQ(expected, s.getState());
}