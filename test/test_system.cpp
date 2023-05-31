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
TEST(System, can_apply_gate) {
    System s1{3}, s2{3};
    Gate* step = new gates::I(0);
    s1.apply(step);
    EXPECT_EQ(s2.getState(), s1.getState());
}
TEST(System, can_apply_vector_of_gates) {
    System s1{3}, s2{3};
    vector<Gate*> v;
    v.push_back(new gates::I(0));
    v.push_back(new gates::I(1));
    v.push_back(new gates::I(2));
    v.push_back(new gates::I(1));
    v.push_back(new gates::I(0));
    s1.apply(v);
    for(Gate* g: v)
        delete g;

    EXPECT_EQ(s2.getState(), s1.getState());
}
TEST(System, can_measure) {
    System s{3};
    EXPECT_EQ(0, s.measure());

    Gate* g = new gates::X(0);
    s.apply(g);
    EXPECT_EQ(4, s.measure());

    delete g;
    g = new gates::X(2);
    s.apply(g);
    EXPECT_EQ(5, s.measure());
}

TEST(System, circuit_from_presentation1) {
    // слайд 5 презентации
    System s{2};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{1.0 / sqrt(2), 0, 1.0 / sqrt(2), 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_from_presentation2) {
    // слайд 6 презентации
    System s{2};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::X(1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{0, 1.0 / sqrt(2), 0, 1.0 / sqrt(2)};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }
}
TEST(System, circuit_from_presentation3) {
    // слайд 8 презентации
    System s{2};

    vector<Gate*> steps;

    Gate* cnot = new gates::CNot(0, 1);
    Matrix m = cnot->getMatrix(2);


    steps.push_back(new gates::H(0));
    steps.push_back(new gates::CNot(0, 1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{1.0 / sqrt(2), 0, 0, 1.0 / sqrt(2)};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s1) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::X(1));
    steps.push_back(new gates::Z(1));
    steps.push_back(new gates::CNot(0, 1));
    steps.push_back(new gates::X(0));
    steps.push_back(new gates::CNot(2, 1));
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::Z(1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{-0.5, 0, 0.5, 0, -0.5, 0, -0.5, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s2) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::CNot(0, 1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{1.0 / sqrt(2), 0, 0, 0, 0, 0, 1.0 / sqrt(2), 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s3) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::X(1));
    steps.push_back(new gates::CNot(1, 0));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{0, 0, 1.0 / sqrt(2), 0, 0, 0, 1.0 / sqrt(2), 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s4) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::X(1));
    steps.push_back(new gates::CNot(1, 0));
    steps.push_back(new gates::X(2));
    steps.push_back(new gates::Z(1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{0, 0, 0, -1.0 / sqrt(2), 0, 0, 0, -1.0 / sqrt(2)};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s5) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::CNot(0, 2));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{1.0 / sqrt(2), 0, 0, 0, 0, 1.0 / sqrt(2), 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s6) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::X(2));
    steps.push_back(new gates::CNot(0, 2));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    vector<Complex> expected{0, 1.0 / sqrt(2), 0, 0, 1.0 / sqrt(2), 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s7) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::H(0));
    steps.push_back(new gates::X(2));
    steps.push_back(new gates::CNot(0, 2));
    steps.push_back(new gates::P(2,M_PI / 2));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    Complex i(0, 1);
    vector<Complex> expected{0, i / sqrt(2), 0, 0, 1.0 / sqrt(2), 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s8) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::P(1,-M_PI / 4));
    steps.push_back(new gates::CNot(0, 1));
    steps.push_back(new gates::P(1,M_PI / 4));
    steps.push_back(new gates::CNot(0, 1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    Complex i(0, 1);
    vector<Complex> expected{1, 0, 0, 0, 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }}
TEST(System, circuit_s9) {
    System s{3};

    vector<Gate*> steps;
    steps.push_back(new gates::X(0));
    steps.push_back(new gates::H(1));
    steps.push_back(new gates::P(1,-M_PI / 4));
    steps.push_back(new gates::CNot(0, 1));
    steps.push_back(new gates::P(1,M_PI / 2));
    steps.push_back(new gates::CNot(0, 1));
    s.apply(steps);
    for(Gate* g: steps)
        delete g;

    Complex i(0, 1);
    vector<Complex> expected{0, 0, 0, 0,  i / sqrt(2), 0, 0.5 - i*0.5, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        double expectedValue = std::abs((expected[j] * expected[j]).real());
        double actualValue = std::abs((actual[j] * actual[j]).real());
        EXPECT_NEAR(expectedValue, actualValue, 1.0e-15);
    }

}