//
// Created by Алексей on 14.05.2023.
//
#include <gtest.h>
#include "Matrix.h"

TEST(Matrix, can_create) {
    ASSERT_NO_THROW(Matrix m(16));
}
TEST(Matrix, can_set_and_get) {
    Matrix m(2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;

    EXPECT_EQ((complex<float>)1, m(0, 0));
    EXPECT_EQ((complex<float>)2, m(0, 1));
    EXPECT_EQ((complex<float>)3, m(1, 0));
    EXPECT_EQ((complex<float>)4, m(1, 1));
}
TEST(Matrix, can_multiply_with_vector) {

    Matrix m(2);
    /*
     * 1 2
     * 3 4
     */
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    Vector v(2);
    // (-1, 1)
    v[0] = -1;
    v[1] = 1;

    Vector res = m*v;
    // (1, 1)

    EXPECT_EQ((complex<float>)1, res[0]);
    EXPECT_EQ((complex<float>)1, res[1]);

}