//
// Created by aleksei on 9/8/23.
//

#include <gtest/gtest.h>
#include "StateVector.h"
// #include <corecrt_math_defines.h>

TEST(StateVector, can_create) {
    ASSERT_NO_THROW(StateVector s(3));
}
TEST(StateVector, can_get_state) {
    StateVector s(3);
    ASSERT_NO_THROW(s.getState());
}
TEST(StateVector, correct_initial_state) {
    StateVector s(3);
    vector<Complex> expected{1, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(expected, s.getState());
}
TEST(StateVector, can_apply_circuit) {
    StateVector s1{3}, s2{3};

    s1.i(0);
    EXPECT_EQ(s2.getState(), s1.getState());
}
TEST(StateVector, can_measure) {
    StateVector s{3};
    EXPECT_EQ(0, s.measure());

    s.x(2);
    EXPECT_EQ(4, s.measure());

    s.x(0);
    EXPECT_EQ(5, s.measure());
}
TEST(StateVector, can_measure_single_qubit) {
    StateVector s{3};

    s.h(0);
    s.h(1);
    s.p(-M_PI / 4, 1);
    s.p(-M_PI / 3, 0);

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
TEST(StateVector, circuit_from_presentation1) {
    // слайд 5 презентации
    StateVector s{2};

    s.h(1);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 1.0 / sqrtf(2), 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_from_presentation2) {
    // слайд 6 презентации
    StateVector s{2};

    s.h(1);
    s.x(0);

    vector<Complex> expected{0, 1.0 / sqrtf(2), 0, 1.0 / sqrtf(2)};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_from_presentation3) {
    // слайд 8 презентации
    StateVector s{2};

    s.h(0);
    s.cnot(0, 1);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 0, 1.0 / sqrtf(2)};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}

TEST(StateVector, circuit_s1) {
    StateVector s{3};

    s.x(1);
    s.h(0);
    s.z(1);
    s.cnot(0, 1);
    s.x(0);
    s.cnot(2, 1);
    s.h(0);
    s.z(1);

    vector<Complex> expected{-0.5, -0.5, 0.5, -0.5, 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(StateVector, circuit_s2) {
    StateVector s{3};


    s.h(0);
    s.cnot(0, 1);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 0, 1.0 / sqrtf(2), 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_s3) {
    StateVector s{3};

    s.h(0);
    s.x(1);
    s.cnot(1, 0);

    vector<Complex> expected{0, 0, 1.0 / sqrtf(2), 1.0 / sqrtf(2), 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_s4) {
    StateVector s{3};

    s.h(0);
    s.x(1);
    s.cnot(1, 0);
    s.x(2);
    s.z(1);

    vector<Complex> expected{0, 0, 0, 0, 0, 0,  -1.0 / sqrtf(2), -1.0 / sqrtf(2)};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_s5) {
    StateVector s{3};

    s.h(0);
    s.cnot(0, 2);

    vector<Complex> expected{1.0 / sqrtf(2), 0, 0, 0, 0, 1.0 / sqrtf(2), 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_s6) {
    StateVector s{3};

    s.h(0);
    s.x(2);
    s.cnot(0, 2);

    vector<Complex> expected{0, 1.0 / sqrtf(2), 0, 0, 1.0 / sqrtf(2), 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_s7) {
    StateVector s{3};

    s.h(0);
    s.x(2);
    s.cnot(0, 2);
    s.p(M_PI / 2, 2);

    Complex i(0, 1);
    vector<Complex> expected{0, 1.0 / sqrtf(2), 0, 0, i / sqrtf(2), 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(StateVector, circuit_s8) {
    StateVector s{3};

    s.p(-M_PI / 4, 1);
    s.cnot(0, 1);
    s.p(M_PI / 4, 1);
    s.cnot(0, 1);

    Complex i(0, 1);
    vector<Complex> expected{1, 0, 0, 0, 0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-15);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-15);
    }
}
TEST(StateVector, circuit_s9) {
    StateVector s{3};

    s.x(0);
    s.h(1);
    s.p(-M_PI / 4, 1 );
    s.cnot(0, 1);
    s.p(M_PI / 2, 1);
    s.cnot(0, 1);

    Complex i(0, 1);
    vector<Complex> expected{0, i / sqrtf(2), 0, 0.5f - i*0.5f,  0, 0, 0, 0};
    vector<Complex> actual = s.getState();

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(StateVector, cry_gate) {
    StateVector s{2};
    s.h(0);
    s.cry(0.1, 0, 1);
    Complex i(0, 1);
    vector<Complex> expected{1/sqrt(2), 1/sqrt(2)*cos(0.05), 0, 1/sqrt(2)*sin(0.05)};
    vector<Complex> actual = s.getState();
    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(StateVector, cry_gate_1) {
    StateVector s{3};

    s.x(0);
    s.h(1);
    s.h(2);
    s.p(-M_PI / 4, 1 );
    s.cnot(0, 1);
    s.p(M_PI / 2, 1);
    s.cnot(0, 1);
    s.cry(0.1, 0, 1);

    Complex i(0, 1);
    vector<Complex> expected{0, -(Complex)0.0176703 + (Complex)0.51704543*i,
         0, (Complex)0.35311154-(Complex)0.32812196*i,  
         0, -(Complex)0.0176703 + (Complex)0.51704543*i,
         0, (Complex)0.35311154-(Complex)0.32812196*i};
    vector<Complex> actual = s.getState();

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(StateVector, u_gate) {
    StateVector s{3};
    vector<Complex> expected = s.getState();
    s.ru(1.1, 2.2, 0.3, 0);
    s.ru(2.1, 2.9, 3.1, 1);
    s.ru(0.5789, 1.9, 2.3456, 2);
    s.ru(-1.1, -0.3, -2.2, 0);
    s.ru(-2.1, -3.1, -2.9, 1);
    s.ru(-0.5789, -2.3456, -1.9, 2);
    vector<Complex> actual = s.getState();
    
    std::cout << expected.size() << " " << actual.size() << std::endl;

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-5);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-5);
    }
}