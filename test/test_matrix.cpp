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

    EXPECT_EQ((Complex)1, m(0, 0));
    EXPECT_EQ((Complex)2, m(0, 1));
    EXPECT_EQ((Complex)3, m(1, 0));
    EXPECT_EQ((Complex)4, m(1, 1));
}
TEST(Matrix, default_size_is_zero) {
    Matrix m;
    EXPECT_EQ(0, m.size());
}
TEST(Matrix, constructor_with_fill_value) {
    Complex value = 1;
    Matrix m{2, value};

    EXPECT_EQ(value, m(0, 0));
    EXPECT_EQ(value, m(0, 1));
    EXPECT_EQ(value, m(1, 0));
    EXPECT_EQ(value, m(1, 1));
}
TEST(Matrix, can_assign) {

    Matrix m(2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;

    Matrix m1(1);
    m1 = m;

    EXPECT_EQ((Complex)1, m1(0, 0));
    EXPECT_EQ((Complex)2, m1(0, 1));
    EXPECT_EQ((Complex)3, m1(1, 0));
    EXPECT_EQ((Complex)4, m1(1, 1));
}
TEST(Matrix, can_add_matrix) {

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

    m1 += m2;

    EXPECT_EQ((Complex)0, m1(0, 0));
    EXPECT_EQ((Complex)4, m1(0, 1));
    EXPECT_EQ((Complex)6, m1(1, 0));
    EXPECT_EQ((Complex)0, m1(1, 1));
}
TEST(Matrix, can_multiply_by_vector) {

    Matrix m(2);
    /*
     * 1 2
     * 5 7
     */
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 5;
    m(1, 1) = 7;
    vector<Complex> v(2);
    // (-1, 1)
    v[0] = -1;
    v[1] = 1;

    vector<Complex> res = m*v;
    // (1, 2)

    EXPECT_EQ((Complex)1, res[0]);
    EXPECT_EQ((Complex)2, res[1]);

}
TEST(Matrix, cant_multiply_with_wrong_size) {
    Matrix m{3};
    vector<Complex> v{4};
    ASSERT_ANY_THROW(m*v);
}
TEST(Matrix, matrix_multiplication) {
    Matrix m1{2};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    /*
     * m1 =
     * 1 2
     * 3 4
     */
    Matrix m2{2, 1};
    /*
     * m2 =
     * 1 1
     * 1 1
     */
    Matrix expected{2};
    expected(0, 0) = 3;
    expected(0, 1) = 3;
    expected(1, 0) = 7;
    expected(1, 1) = 7;
    /*
     * m1 * m2 =
     * 3 3
     * 7 7
     */

    Matrix actual = m1 * m2;
    std:: cout << actual.size() << std::endl;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            std::cout << actual(i, j) << " ";
        }
        std::cout << std::endl;
    }
    EXPECT_EQ(expected, m1 * m2);
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

    EXPECT_EQ((Complex)-1, result(0, 0));
    EXPECT_EQ((Complex)2, result(0, 1));
    EXPECT_EQ((Complex)-2, result(0, 2));
    EXPECT_EQ((Complex)4, result(0, 3));
    EXPECT_EQ((Complex)3, result(1, 0));
    EXPECT_EQ((Complex)-4, result(1, 1));
    EXPECT_EQ((Complex)6, result(1, 2));
    EXPECT_EQ((Complex)-8, result(1, 3));
    EXPECT_EQ((Complex)-3, result(2, 0));
    EXPECT_EQ((Complex)6, result(2, 1));
    EXPECT_EQ((Complex)-4, result(2, 2));
    EXPECT_EQ((Complex)8, result(2, 3));
    EXPECT_EQ((Complex)9, result(3, 0));
    EXPECT_EQ((Complex)-12, result(3, 1));
    EXPECT_EQ((Complex)12, result(3, 2));
    EXPECT_EQ((Complex)-16, result(3, 3));

}
