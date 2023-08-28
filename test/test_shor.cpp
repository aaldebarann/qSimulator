//
// Created by aleksei on 28.08.23.
//

#include "gtest.h"
#include "System.h"

TEST(cMultMod, can_apply) {
    System s(10);
    Circuit* circ = new Circuit(10);
    circ->cMultMod(2, 3, 0, 1, 2, false);
    ASSERT_NO_THROW(s.apply(*circ));
    delete circ;
}
TEST(cMultMod, can_apply_approximate) {
    System s(10);
    Circuit* circ = new Circuit(10);
    circ->cMultMod(2, 3, 0, 1, 2, true);
    ASSERT_NO_THROW(s.apply(*circ));
    delete circ;
}
TEST(cMultMod, control_qubit_is_zero) {
    System s1(10), s2(10);

    Circuit* init = new Circuit(10);
    init->x(1);
    init->x(2);
    init->x(7);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(10);
    circ->cMultMod(1, 3, 0, 1, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(cMultMod, _0_plus_2_mul_2_mod_3) {
    System s1(10), s2(10);

    Circuit* init = new Circuit(10);
    init->x(0);
    init->x(1);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(10);
    circ->cMultMod(2, 3, 0, 1, 2, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(10);
    expect->x(0);
    expect->x(1);
    expect->x(8);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(cMultMod, _2_plus_1_mul_3_mod_3) {
    System s1(10), s2(10);

    Circuit* init = new Circuit(10);
    init->x(0);
    init->x(1);
    init->x(2);
    init->x(7);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(10);
    circ->cMultMod(1, 3, 0, 1, 2, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(10);
    expect->x(0);
    expect->x(1);
    expect->x(2);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(cMultMod, _1_plus_2_mul_2_mod_3) {
    System s1(10), s2(10);

    Circuit* init = new Circuit(10);
    init->x(0);
    init->x(1);
    init->x(8);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(10);
    circ->cMultMod(2, 3, 0, 1, 2, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(10);
    expect->x(0);
    expect->x(1);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(cMultMod, _2_plus_1_mul_3_mod_3_approximate) {
    System s1(10), s2(10);

    Circuit* init = new Circuit(10);
    init->x(0);
    init->x(1);
    init->x(2);
    init->x(7);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(10);
    circ->cMultMod(1, 3, 0, 1, 2, true);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(10);
    expect->x(0);
    expect->x(1);
    expect->x(2);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(cMultMod, _1_plus_2_mul_2_mod_3_approximate) {
    System s1(10), s2(10);

    Circuit* init = new Circuit(10);
    init->x(0);
    init->x(1);
    init->x(8);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(10);
    circ->cMultMod(2, 3, 0, 1, 2, true);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(10);
    expect->x(0);
    expect->x(1);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}