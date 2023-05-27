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
TEST(System, correct_initial_state) {
    System s(3);
    vector<Complex> expected{1, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(expected, s.getState());
}
TEST(System, identity_circuit) {
    System s1{3}, s2{3};
    Matrix step = I(1, 3);
    s1.apply(step);
    EXPECT_EQ(s2.getState(), s1.getState());
}