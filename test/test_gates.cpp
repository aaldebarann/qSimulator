//
// Created by aleksei on 27.05.23.
//
#include <gtest.h>
#include "Gates.h"

TEST(Gates, correct_i) {
    Matrix expected{8, 0};
    for(int i = 0; i < 8; i++)
        expected(i, i) = 1;

    Matrix* actual = forSystem(I(), 1, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_x) {
    Matrix expected{8, 0};
    expected(0, 2) = 1;
    expected(1, 3) = 1;
    expected(2, 0) = 1;
    expected(3, 1) = 1;
    expected(4, 6) = 1;
    expected(5, 7) = 1;
    expected(6, 4) = 1;
    expected(7, 5) = 1;

    Matrix* actual = forSystem(X(), 1, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_y) {
    Matrix expected{8, 0};
    Complex i{0, 1};
    expected(0, 2) = -i;
    expected(1, 3) = -i;
    expected(2, 0) = i;
    expected(3, 1) = i;
    expected(4, 6) = -i;
    expected(5, 7) = -i;
    expected(6, 4) = i;
    expected(7, 5) = i;

    Matrix* actual = forSystem(Y(), 1, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_z) {
    Matrix expected{8, 0};
    expected(0, 0) = 1;
    expected(1, 1) = 1;
    expected(2, 2) = -1;
    expected(3, 3) = -1;
    expected(4, 4) = 1;
    expected(5, 5) = 1;
    expected(6, 6) = -1;
    expected(7, 7) = -1;

    Matrix* actual = forSystem(Z(), 1, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_h) {
    Matrix expected{8, 0};

    double tmp = 1.0 / sqrt(2);

    expected(0, 0) = tmp;
    expected(0, 2) = tmp;
    expected(1, 1) = tmp;
    expected(1, 3) = tmp;
    expected(2, 0) = tmp;
    expected(2, 2) = -tmp;
    expected(3, 1) = tmp;
    expected(3, 3) = -tmp;
    expected(4, 4) = tmp;
    expected(4, 6) = tmp;
    expected(5, 5) = tmp;
    expected(5, 7) = tmp;
    expected(6, 4) = tmp;
    expected(6, 6) = -tmp;
    expected(7, 5) = tmp;
    expected(7, 7) = -tmp;

    Matrix* actual = forSystem(H(), 1, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_p) {

    Matrix* expected = forSystem(Z(), 1, 3);

    Matrix* actual = forSystem(P(M_PI), 1, 3);

    for(int i = 0; i < expected->size(); i++) {
        for(int j = 0; j < expected->size(); j++) {
            double deviation = ((*expected)(i, j)*(*expected)(i, j) - (*actual)(i, j)*(*actual)(i, j)).real();
            EXPECT_TRUE(deviation < 0.001);
        }
    }
    delete expected;
    delete actual;
}
TEST(Gates, correct_cnot) {
    Matrix expected{8, 0};

    expected(0, 0) = 1;
    expected(1, 5) = 1;
    expected(2, 2) = 1;
    expected(3, 7) = 1;
    expected(4, 4) = 1;
    expected(5, 1) = 1;
    expected(6, 6) = 1;
    expected(7, 3) = 1;

    Matrix* actual = CNOT(0, 2, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_ccnot) {
    Matrix expected{8, 0};

    expected(0, 0) = 1;
    expected(1, 1) = 1;
    expected(2, 2) = 1;
    expected(3, 3) = 1;
    expected(4, 4) = 1;
    expected(5, 5) = 1;
    expected(6, 7) = 1;
    expected(7, 6) = 1;

    Matrix* actual = CCNOT(2, 1, 0, 3);

    EXPECT_EQ(expected, *actual);
    delete actual;
}
TEST(Gates, correct_cphase) {
    Matrix expected{4, 0};

    Complex phi = M_PI;

    expected(0, 0) = 1;
    expected(1, 1) = 1;
    expected(2, 2) = 1;
    expected(3, 3) = -1;

    Matrix* actual = CPHASE(phi, 0, 1, 2);

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            EXPECT_NEAR(expected(i, j).real(), (*actual)(i, j).real(), 1.0e-7);
            EXPECT_NEAR(expected(i, j).imag(), (*actual)(i, j).imag(), 1.0e-7);
        }
    }
    delete actual;
}