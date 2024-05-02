//
// Created by aleksei on 28.08.23.
//

#include <gtest/gtest.h>
#include "System.h"
#include "StateVector.h"
#include "shor.h"

TEST(test_shor_classic, prime_number_is_not_perfect_power) {
    EXPECT_EQ(0, perfectPower(2));
    EXPECT_EQ(0, perfectPower(7));
    EXPECT_EQ(0, perfectPower(19));
    EXPECT_EQ(0, perfectPower(541));
    EXPECT_EQ(0, perfectPower(7309));
}
TEST(test_shor_classic, number_is_not_perfect_power) {
    EXPECT_EQ(0, perfectPower(6));
    EXPECT_EQ(0, perfectPower(12));
    EXPECT_EQ(0, perfectPower(1001));
    EXPECT_EQ(0, perfectPower(6144));
    EXPECT_EQ(0, perfectPower(25482));
}
TEST(test_shor_classic, number_is_perfect_power) {
    EXPECT_EQ(2, perfectPower(4));
    EXPECT_EQ(8, perfectPower(64));
    EXPECT_EQ(7, perfectPower(16807));
    EXPECT_EQ(2, perfectPower(8192));
    EXPECT_EQ(27, perfectPower(19683));
}
TEST(test_shor_classic, classic_version) {
    int a[] = {1011,561, 1105, 1729, 2465,
               2821};
    EXPECT_EQ(0, 1011 % shor_classic(1011));
    EXPECT_EQ(0, 561 % shor_classic(561));
    EXPECT_EQ(0, 1105 % shor_classic(1105));
    EXPECT_EQ(0, 1729 % shor_classic(1729));
    EXPECT_EQ(0, 2465 % shor_classic(2465));
    EXPECT_EQ(0, 2821 % shor_classic(2821));
}

TEST(cMultMod, can_apply) {
    StateVector* s = new StateVector(11);
    ASSERT_NO_THROW(s->cMultMod(9, 15, 0, 1, 4, false));
    delete s;
}
TEST(cMultMod, can_apply_approximate) {
    StateVector* s = new StateVector(11);
    ASSERT_NO_THROW(s->cMultMod(9, 15, 0, 1, 4, true));
    delete s;
}
TEST(cMultMod, control_qubit_is_zero) {
    StateVector* s1 = new StateVector(11);
    StateVector* s2 = new StateVector(11);

    s1->x(1);
    s1->x(2);
    s1->x(7);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    s1->cMultMod(9, 15, 0, 1, 4, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _11_plus_4_mul_3_mod_14) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);
    s->x(9);

    s->cMultMod(4, 14, 0, 1, 4, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1  + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(cMultMod, _10_plus_4_mul_7_mod_14) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(2);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->cMultMod(4, 14, 0, 1, 4, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 8);

    EXPECT_EQ(expected, actual);
}
TEST(cMultMod, _10_plus_5_mul_3_mod_12) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->cMultMod(5, 12, 0, 1, 4, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 3) + (1 << 4) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(cMultMod, _11_plus_4_mul_3_mod_14_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);
    s->x(9);

    s->cMultMod(4, 14, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1  + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(cMultMod, _10_plus_4_mul_7_mod_14_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(2);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->cMultMod(4, 14, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 8);

    EXPECT_EQ(expected, actual);
}
TEST(cMultMod, _10_plus_5_mul_3_mod_12_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->cMultMod(5, 12, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 3) + (1 << 4) + (1 << 9);

    EXPECT_EQ(expected, actual);
}

TEST(icMultMod, can_apply) {
    StateVector* s = new StateVector(11);
    ASSERT_NO_THROW(s->icMultMod(9, 15, 0, 1, 4, false));
    delete s;
}
TEST(icMultMod, can_apply_approximate) {
    StateVector* s = new StateVector(11);
    ASSERT_NO_THROW(s->icMultMod(9, 15, 0, 1, 4, true));
    delete s;
}
TEST(icMultMod, control_qubit_is_zero) {
    StateVector* s1 = new StateVector(11);
    StateVector* s2 = new StateVector(11);

    s1->x(1);
    s1->x(2);
    s1->x(7);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    s1->icMultMod(9, 15, 0, 1, 4, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(icMultMod, _11_minus_4_mul_3_mod_14) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);
    s->x(9);

    s->icMultMod(4, 14, 0, 1, 4, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1  + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 7) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, _10_minus_4_mul_7_mod_14) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(2);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->icMultMod(4, 14, 0, 1, 4, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 8);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, _10_minus_5_mul_3_mod_12) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->icMultMod(5, 12, 0, 1, 4, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 3) + (1 << 4) + (1 << 7) + (1 << 8) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, _11_minus_4_mul_3_mod_14_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);
    s->x(9);

    s->icMultMod(4, 14, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1  + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 7) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, _10_minus_4_mul_7_mod_14_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(2);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->icMultMod(4, 14, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 8);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, _10_minus_5_mul_3_mod_12_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(6);
    s->x(8);

    s->icMultMod(5, 12, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 3) + (1 << 4) + (1 << 7) + (1 << 8) + (1 << 9);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, _5_minus_12_mul_8_mod_103) {
    StateVector* s = new StateVector(17);

    s->x(0);
    s->x(4);
    s->x(5);
    s->x(13);
    s->x(15);

    s->icMultMod(8, 103, 0, 1, 7);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 4) + (1 << 5) + (1 << 12) + (1 << 13);

    EXPECT_EQ(expected, actual);
}
TEST(icMultMod, inverse_to_cMultMod) {

    StateVector* s = new StateVector(11);

    s->x(0);
    s->x(3);
    s->x(4);
    s->x(7);
    s->x(8);
    s->x(9);

    s->cMultMod(5, 12, 0, 1, 4, true);
    s->icMultMod(5, 12, 0, 1, 4, true);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 3) + (1 << 4) + (1 << 7) + (1 << 8) + (1 << 9);

    EXPECT_EQ(expected, actual);
}

TEST(controlledUa, can_apply) {
    StateVector* s = new StateVector(11);
    ASSERT_NO_THROW(s->u(7, 15, 0, 1, 4, false));
    delete s;
}
TEST(controlledUa, control_qubit_is_zero) {
    StateVector* s1 = new StateVector(11);
    StateVector* s2 = new StateVector(11);

    s1->x(1);
    s1->x(3);
    s1->x(4);
    s1->u(7, 15, 0, 1, 4, false);

    s2->x(1);
    s2->x(3);
    s2->x(4);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _5_mul_5_mod_13) {
    StateVector* s = new StateVector(11);

    s->x(0);

    s->x(2);
    s->x(4);
    s->u(5, 13, 0, 1, 4, false);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 1) + (1 << 2);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(controlledUa, _2_mul_3_mod_31) {
    StateVector* s = new StateVector(13);

    s->x(0);
    s->x(4);
    s->u(3, 31, 0, 1, 5, false);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 3) + (1 << 4);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(controlledUa, _12_mul_24_mod_29) {
    StateVector* s = new StateVector(13);

    s->x(0);
    s->x(2);
    s->x(3);
    s->u(24, 29, 0, 1, 5, false);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 1) + (1 << 2) + (1 << 4) + (1 << 5);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(controlledUa, _21_mul_22_mod_23) {
    StateVector* s = new StateVector(13);

    s->x(0);
    s->x(1);
    s->x(3);
    s->x(5);
    s->u(22, 23, 0, 1, 5, false);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 4);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(controlledUa, _5_mul_5_mod_13_approximate) {
    StateVector* s = new StateVector(11);

    s->x(0);

    s->x(2);
    s->x(4);
    s->u(5, 13, 0, 1, 4, true);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 1) + (1 << 2);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(DISABLED_controlledUa, _2_mul_3_mod_31_approximate) {
    StateVector* s = new StateVector(13);

    s->x(0);
    s->x(4);
    s->u(3, 31, 0, 1, 5, true);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 3) + (1 << 4);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(DISABLED_controlledUa, _12_mul_24_mod_29_approximate) {
    StateVector* s = new StateVector(13);

    s->x(0);
    s->x(2);
    s->x(3);
    s->u(24, 29, 0, 1, 5, true);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 1) + (1 << 2) + (1 << 4) + (1 << 5);

    EXPECT_EQ(expected, actual);
    delete s;
}
TEST(DISABLED_controlledUa, _21_mul_22_mod_23_approximate) {
    StateVector* s = new StateVector(13);

    s->x(0);
    s->x(1);
    s->x(3);
    s->x(5);
    s->u(22, 23, 0, 1, 5, true);

    size_t actual = s->measure();
    size_t expected = 1 + (1 << 4);

    EXPECT_EQ(expected, actual);
    delete s;
}

TEST(test_shor_quantum, _6) {
    EXPECT_EQ(0, 6 % shor_quantum(6, 3));
}
TEST(test_shor_quantum, _10) {
    EXPECT_EQ(0, 10 % shor_quantum(10, 4));
}
TEST(test_shor_quantum, _12) {
    EXPECT_EQ(0, 12 % shor_quantum(12, 4));
}
TEST(test_shor_quantum, _15) {
    EXPECT_EQ(0, 15 % shor_quantum(15, 4));
}
TEST(test_shor_quantum, _18) {
    EXPECT_EQ(0, 18 % shor_quantum(18, 5));
}
TEST(test_shor_quantum, _28) {
    EXPECT_EQ(0, 28 % shor_quantum(28, 5));
}
