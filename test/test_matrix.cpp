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
TEST(Matrix, can_multiply_by_vector) {

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
TEST(Matrix, kronecker_product) {

    Matrix m1(2);
    /*
     * 1 2
     * 3 4
     */
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2);
    /*
     * -1 2
     * 3 -4
     */
    m2(0, 0) = -1;
    m2(0, 1) = 2;
    m2(1, 0) = 3;
    m2(1, 1) = -4;
    /*
     * -1   2  -2  4
     *  3  -4   6 -8
     * -3   6  -4  8
     *  9 -12  12 -16
     */
    Matrix result = m1.kron(m2);

    EXPECT_EQ((complex<float>)-1, result(0, 0));
    EXPECT_EQ((complex<float>)2, result(0, 1));
    EXPECT_EQ((complex<float>)-2, result(0, 2));
    EXPECT_EQ((complex<float>)4, result(0, 3));
    EXPECT_EQ((complex<float>)3, result(1, 0));
    EXPECT_EQ((complex<float>)-4, result(1, 1));
    EXPECT_EQ((complex<float>)6, result(1, 2));
    EXPECT_EQ((complex<float>)-8, result(1, 3));
    EXPECT_EQ((complex<float>)-3, result(2, 0));
    EXPECT_EQ((complex<float>)6, result(2, 1));
    EXPECT_EQ((complex<float>)-4, result(2, 2));
    EXPECT_EQ((complex<float>)8, result(2, 3));
    EXPECT_EQ((complex<float>)9, result(3, 0));
    EXPECT_EQ((complex<float>)-12, result(3, 1));
    EXPECT_EQ((complex<float>)12, result(3, 2));
    EXPECT_EQ((complex<float>)-16, result(3, 3));

}