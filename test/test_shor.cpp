//
// Created by aleksei on 28.08.23.
//

#include "gtest.h"
#include "System.h"
#include "StateVector.h"

TEST(cMultMod, can_apply) {
    StateVector* s = new StateVector(10);
    ASSERT_NO_THROW(s->cMultMod(2, 3, 0, 1, 2, false));
    delete s;
}
TEST(cMultMod, can_apply_approximate) {
    StateVector* s = new StateVector(10);
    ASSERT_NO_THROW(s->cMultMod(2, 3, 0, 1, 2, true));
    delete s;
}
TEST(cMultMod, control_qubit_is_zero) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(1);
    s1->x(2);
    s1->x(7);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    s1->cMultMod(1, 3, 0, 1, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _0_plus_2_mul_2_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->cMultMod(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);
    s2->x(8);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _2_plus_1_mul_3_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(2);
    s1->x(7);
    s1->cMultMod(1, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _1_plus_2_mul_2_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(8);
    s1->cMultMod(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _1_plus_2_mul_1_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(2);
    s1->x(8);
    s1->cMultMod(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(2);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _0_plus_2_mul_2_mod_3_apprpximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->cMultMod(2, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(1);
    s2->x(8);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _2_plus_1_mul_3_mod_3_approximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(2);
    s1->x(7);
    s1->cMultMod(1, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _1_plus_2_mul_2_mod_3_approximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(8);
    s1->cMultMod(2, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(1);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, _1_plus_2_mul_1_mod_3_approximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(2);
    s1->x(8);
    s1->cMultMod(2, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(2);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(cMultMod, is_inverse_to_icMultMod) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(8);
    s2->x(0);
    s2->x(1);
    s2->x(8);

    s1->cMultMod(2, 3, 0, 1, 2, false);
    s1->icMultMod(2, 3, 0, 1, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}

TEST(icMultMod, _2_minus_1_mul_3_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(2);
    s1->x(7);
    s1->icMultMod(1, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(icMultMod, _1_minus_2_mul_2_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(8);
    s1->icMultMod(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(icMultMod, _1_minus_2_mul_1_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(2);
    s1->x(8);
    s1->icMultMod(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(2);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(icMultMod, _2_minus_1_mul_3_mod_3_approximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(2);
    s1->x(7);
    s1->icMultMod(1, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(1);
    s2->x(2);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(icMultMod, _1_minus_2_mul_2_mod_3_approximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(8);
    s1->icMultMod(2, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(1);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(icMultMod, _1_minus_2_mul_1_mod_3_approximate) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(2);
    s1->x(8);
    s1->icMultMod(2, 3, 0, 1, 2, true);

    s2->x(0);
    s2->x(2);
    s2->x(7);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}

TEST(controlledUa, can_apply) {
    StateVector* s = new StateVector(10);
    ASSERT_NO_THROW(s->u(2, 3, 0, 1, 2, false));
    delete s;
}
TEST(controlledUa, control_qubit_is_zero) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(1);
    s1->u(2, 3, 0, 1, 2, false);

    s2->x(1);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _2_mul_2_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->u(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(2);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _3_mul_1_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(2);
    s1->u(3, 3, 0, 1, 2, false);

    s2->x(0);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _1_mul_2_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->u(1, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _2_mul_1_mod_3) {

    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(2);
    s1->u(2, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _0_mul_3_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(2);
    s1->u(0, 3, 0, 1, 2, false);

    s2->x(0);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
TEST(controlledUa, _1_mul_3_mod_3) {
    StateVector* s1 = new StateVector(10);
    StateVector* s2 = new StateVector(10);

    s1->x(0);
    s1->x(1);
    s1->x(2);
    s1->u(1, 3, 0, 1, 2, false);

    s2->x(0);
    s2->x(1);
    s2->x(2);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
    delete s1;
    delete s2;
}
