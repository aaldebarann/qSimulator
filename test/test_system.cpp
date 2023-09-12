//
// Created by Алексей on 15.05.2023.
//

#include <gtest.h>
#include "System.h"
// #include <corecrt_math_defines.h>

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
TEST(System, can_apply_circuit) {
    System s1{3}, s2{3};

    Circuit circ(3);
    circ.i(0);

    s1.apply(circ);

    EXPECT_EQ(s2.getState(), s1.getState());
}
TEST(System, can_measure) {
    System s{3};
    EXPECT_EQ(0, s.measure());

    Circuit circ(3);
    circ.x(2);
    s.apply(circ);
    EXPECT_EQ(4, s.measure());

    Circuit circ1(3);
    circ1.x(0);
    s.apply(circ1);
    EXPECT_EQ(5, s.measure());
}
TEST(System, can_measure_single_qubit) {
    System s{3};

    Circuit circ(3);
    circ.h(0);
    circ.h(1);
    circ.p(-M_PI / 4, 1);
    circ.p(-M_PI / 3, 0);
    s.apply(circ);

    s.measure(0);
    s.measure(1);
    s.measure(2);
    vector<Complex> state = s.getState();

    double norm = 0;
    int count = 0;
    Complex zero(0);
    for(int i = 0; i < state.size(); i++) {
        norm += state[i].real() * state[i].real();
        norm += state[i].imag() * state[i].imag();
        if(state[i] != zero)
            count++;
    }
    norm = std::sqrt(norm);
    EXPECT_FLOAT_EQ(1.0f, norm);
    EXPECT_EQ(1, count);
}
TEST(System, circuit_from_presentation1) {
    // слайд 5 презентации
    System s{2};

    Circuit circ(2);
    circ.h(1);
    s.apply(circ);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 1.0 / sqrtf(2), 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(System, circuit_from_presentation2) {
    // слайд 6 презентации
    System s{2};

    Circuit circ(2);
    circ.h(1);
    circ.x(0);
    s.apply(circ);

    vector<Complex> expected{0, 1.0 / sqrtf(2), 0, 1.0 / sqrtf(2)};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(System, circuit_from_presentation3) {
    // слайд 8 презентации
    System s{2};

    Circuit circ(2);
    circ.h(0);
    circ.cnot(0, 1);
    s.apply(circ);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 0, 1.0 / sqrtf(2)};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}

TEST(System, circuit_s1) {
    System s{3};

    Circuit circ(3);
    circ.x(1);
    circ.h(0);
    circ.z(1);
    circ.cnot(0, 1);
    circ.x(0);
    circ.cnot(2, 1);
    circ.h(0);
    circ.z(1);
    s.apply(circ);

    vector<Complex> expected{-0.5, -0.5, 0.5, -0.5, 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
     for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(System, circuit_s2) {
    System s{3};


    Circuit circ(3);
    circ.h(0);
    circ.cnot(0, 1);
    s.apply(circ);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 0, 1.0 / sqrtf(2), 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(System, circuit_s3) {
    System s{3};

    Circuit circ(3);
    circ.h(0);
    circ.x(1);
    circ.cnot(1, 0);
    s.apply(circ);

    vector<Complex> expected{0, 0, 1.0 / sqrtf(2), 1.0 / sqrtf(2), 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(System, circuit_s4) {
    System s{3};

    Circuit circ(3);
    circ.h(0);
    circ.x(1);
    circ.cnot(1, 0);
    circ.x(2);
    circ.z(1);
    s.apply(circ);

    vector<Complex> expected{0, 0, 0, 0, 0, 0,  -1.0 / sqrtf(2), -1.0 / sqrtf(2)};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
       }
}
TEST(System, circuit_s5) {
    System s{3};

    Circuit circ(3);
    circ.h(0);
    circ.cnot(0, 2);
    s.apply(circ);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 0, 0, 0, 1.0 / sqrtf(2), 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
       }
}
TEST(System, circuit_s6) {
    System s{3};

    Circuit circ(3);
    circ.h(0);
    circ.x(2);
    circ.cnot(0, 2);
    s.apply(circ);

    vector<Complex> expected{0, 1.0 / sqrtf(2), 0, 0, 1.0 / sqrtf(2), 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
       }
}
TEST(System, circuit_s7) {
    System s{3};


    Circuit circ(3);
    circ.h(0);
    circ.x(2);
    circ.cnot(0, 2);
    circ.p(M_PI / 2, 2);
    s.apply(circ);

    Complex i(0, 1);
    vector<Complex> expected{0, 1.0 / sqrtf(2), 0, 0, i / sqrtf(2), 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
       }
}
TEST(System, circuit_s8) {
    System s{3};

    Circuit circ(3);
    circ.p(-M_PI / 4, 1);
    circ.cnot(0, 1);
    circ.p(M_PI / 4, 1);
    circ.cnot(0, 1);
    s.apply(circ);

    Complex i(0, 1);
    vector<Complex> expected{1, 0, 0, 0, 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
         EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
         EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
       }
}
TEST(System, circuit_s9) {
    System s{3};

    Circuit circ(3);
    circ.x(0);
    circ.h(1);
    circ.p(-M_PI / 4, 1 );
    circ.cnot(0, 1);
    circ.p(M_PI / 2, 1);
    circ.cnot(0, 1);
    s.apply(circ);

    Complex i(0, 1);
    vector<Complex> expected{0, i / sqrtf(2), 0, 0.5f - i*0.5f,  0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
