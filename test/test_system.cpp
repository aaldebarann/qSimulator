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
    vector<Complex> expected{0, 0, 0, 0, 0, 0, 0, 0};
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
TEST(System, circuit_s2) {
    System s{3};

    vector<Matrix> step1;
    step1.push_back(H());
    step1.push_back(I());
    step1.push_back(I());
    s.apply(step1);

    vector<Matrix> step2;
    step2.push_back(H());
    step2.push_back(I());
    step2.push_back(I());

}