//
// Created by Алексей on 14.05.2023.
//

#include <gtest.h>
#include "Vector.h"

TEST(Vector, can_create) {
    ASSERT_NO_THROW(Vector v(16));
}
TEST(Vector, can_set_and_get) {
    Vector v(4);
    v[0] = 0;
    v[1] = 1;
    v[2] = 2;
    v[3] = 3;

    EXPECT_EQ((complex<float>)0,v[0]);
    EXPECT_EQ((complex<float>)1,v[1]);
    EXPECT_EQ((complex<float>)2, v[2]);
    EXPECT_EQ((complex<float>)3, v[3]);
}
TEST(Vector, can_create_and_fill) {
    Vector v(4, 0);

    complex<float> expected(0);
    EXPECT_EQ(expected,v[0]);
    EXPECT_EQ(expected,v[1]);
    EXPECT_EQ(expected, v[2]);
    EXPECT_EQ(expected, v[3]);
}
