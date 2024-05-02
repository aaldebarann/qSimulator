//
// Created by Алексей on 13.07.2023.
//

#include "Addition.h"
#include <gtest/gtest.h>
#include "System.h"
#include "StateVector.h"

TEST(add, classic_3bit_circuit_no_matrix) {
    StateVector s{10};

    s.x(2);
    s.x(7);
    s.x(8);
    s.add(3);

    size_t res = s.measure();
    EXPECT_EQ(res, 644);
}
TEST(add, classic_addition) {
    EXPECT_EQ(3, classicalAdd(1, 2, 2));
    EXPECT_EQ(3, classicalAdd(0, 3, 2));
    EXPECT_EQ(4, classicalAdd(1, 3, 2));
    EXPECT_EQ(9, classicalAdd(4, 5, 3));
    EXPECT_EQ(11, classicalAdd(5, 6, 3));
    EXPECT_EQ(11, classicalAdd(4, 7, 3));
    EXPECT_EQ(14, classicalAdd(7, 7, 3));
    EXPECT_EQ(10, classicalAdd(4, 6, 3));
    EXPECT_EQ(6, classicalAdd(2, 4, 3));
    EXPECT_EQ(12, classicalAdd(5, 7, 3));
    //EXPECT_EQ(109, classicalAdd(46, 63, 6));
}

TEST(qadd, can_apply_qadd_circuit) {
    System s(7);
    Circuit circ(7);
    circ.qadd(0, 3);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qadd, can_apply_iqadd_circuit) {
    System s(7);
    Circuit circ(7);
    circ.iqadd(0, 3);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qadd, qadd_is_inverse_to_iqadd) {
    System s1(7), s2(7);
    Circuit init(7);
    init.h(0);
    init.x(1);
    init.y(2);
    init.h(2);
    init.z(2);
    s1.apply(init);
    s2.apply(init);

    Circuit circ(7);
    circ.qadd(0, 3);
    circ.iqadd(0, 3);

    s1.apply(circ);

    vector<Complex> expected, actual;
    expected = s2.getState();
    actual = s1.getState();

    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-6);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-6);
    }
}
TEST(qadd, quantum) {
    EXPECT_EQ(3, quantumAdd(1, 2, 4));
    EXPECT_EQ(3, quantumAdd(0, 3, 2));
    EXPECT_EQ(0, quantumAdd(1, 3, 2));
    EXPECT_EQ(1, quantumAdd(4, 5, 3));
    EXPECT_EQ(3, quantumAdd(5, 6, 3));
    EXPECT_EQ(3, quantumAdd(4, 7, 3));
    EXPECT_EQ(6, quantumAdd(7, 7, 3));
    EXPECT_EQ(11, quantumAdd(12, 15, 4));
    EXPECT_EQ(2, quantumAdd(11, 7, 4));
    EXPECT_EQ(28, quantumAdd(31, 29, 5));
    EXPECT_EQ(27, quantumAdd(28, 31, 5));
    EXPECT_EQ(507, quantumAdd(317, 190, 9));
}
TEST(qadd, quantum_approximate) {
    EXPECT_EQ(3, quantumAdd(1, 2, 4, true));
    EXPECT_EQ(3, quantumAdd(0, 3, 2, true));
    EXPECT_EQ(0, quantumAdd(1, 3, 2, true));
    EXPECT_EQ(1, quantumAdd(4, 5, 3, true));
    EXPECT_EQ(3, quantumAdd(5, 6, 3, true));
    EXPECT_EQ(3, quantumAdd(4, 7, 3, true));
    EXPECT_EQ(6, quantumAdd(7, 7, 3, true));
    EXPECT_EQ(11, quantumAdd(12, 15, 4, true));
    EXPECT_EQ(2, quantumAdd(11, 7, 4, true));
    EXPECT_EQ(28, quantumAdd(31, 29, 5, true));
    EXPECT_EQ(27, quantumAdd(28, 31, 5, true));
    EXPECT_EQ(507, quantumAdd(317, 190, 9, true));
}

TEST(qadd, reverse_qadd_positive_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 11;
    b = 14;
    StateVector* s = new StateVector( bits);
    // кодируем слагаемое в состоянии системы
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            s->x(bits - 1 - i);
        b /= 2;
    }
    // к слагаемому b необходимо применить КПФ
    s->qft(0, bits, false);
    // схема квантового сложения
    s->iqadd(a, 0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    s->iqft(0, bits, false);
    // измеряем состояние системы
    unsigned res = s->measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(3, sum);
    delete s;
}
TEST(qadd, reverse_qadd_negative_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 14;
    b = 11;
    StateVector* s = new StateVector(bits);
    // кодируем слагаемые в состоянии системы
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            s->x(bits - 1 - i);
        b /= 2;
    }
    // к слагаемому a необходимо применить КПФ
    s->qft(0, bits, false);
    // схема квантового сложения
    s->iqadd(a, 0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    s->iqft(0, bits, false);
    // измеряем состояние системы
    unsigned res = s->measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(13, sum);
    delete s;
}

TEST(test_qadd_1c, control_qubit_in_zero_state) {
    StateVector* s1 = new StateVector(5);
    StateVector* s2 = new StateVector(5);
    s1->x(1);
    s1->x(3);
    s2->x(1);
    s2->x(3);

    s1->qadd_1c(3, 0, 1, 4, false);

    EXPECT_EQ(s2->getState(), s1->getState());
    delete s1;
    delete s2;
}
TEST(test_qadd_1c, qadd_is_inverse_to_iqadd) {
    StateVector* s1 = new StateVector(5);
    StateVector* s2 = new StateVector(5);

    s1->h(0);
    s1->x(1);
    s1->y(2);
    s1->h(2);
    s1->z(2);
    s1->x(4);
    s2->h(0);
    s2->x(1);
    s2->y(2);
    s2->h(2);
    s2->z(2);
    s2->x(4);

    s1->qadd_1c(6, 4, 0, 3);
    s1->iqadd_1c(6, 4, 0, 3);

    vector<Complex> expected, actual;
    expected = s2->getState();
    actual = s1->getState();

    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-6);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}

TEST(test_qadd_2c, control_qubit_in_zero_state) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);
    s1->h(1);
    s1->h(3);
    s2->h(1);
    s2->h(3);

    s1->qadd_2c(3, 4, 5, 0, 4, false);

    EXPECT_EQ(s2->getState(), s1->getState());
    delete s1;
    delete s2;
}
TEST(test_iqadd_2c, control_qubit_in_zero_state) {

    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);
    s1->h(1);
    s1->h(3);
    s2->h(1);
    s2->h(3);

    s1->iqadd_2c(3, 4, 5, 0, 4, false);

    EXPECT_EQ(s2->getState(), s1->getState());
    delete s1;
    delete s2;
}
TEST(test_qadd_2c, qadd_is_inverse_to_iqadd) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->h(0);
    s1->x(1);
    s1->y(2);
    s1->h(2);
    s1->z(2);

    s1->x(4);
    s1->x(5);

    s2->h(0);
    s2->x(1);
    s2->y(2);
    s2->h(2);
    s2->z(2);

    s2->x(4);
    s2->x(5);

    s1->qadd_2c(6, 4, 5, 0, 3);
    s1->iqadd_2c(6, 4, 5, 0, 3);

    vector<Complex> expected, actual;
    expected = s2->getState();
    actual = s1->getState();

    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-6);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qadd_2c, reverse_qadd_positive_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 11;
    b = 14;
    StateVector* s = new StateVector( bits + 2);
    // кодируем слагаемое в состоянии системы
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            s->x(bits - 1 - i);
        b /= 2;
    }
    s->x(4);
    s->x(5);
    // к слагаемому b необходимо применить КПФ
    s->qft(0, bits, false);
    // схема квантового сложения
    s->iqadd_2c(a, 4, 5, 0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    s->iqft(0, bits, false);
    // измеряем состояние системы
    unsigned res = s->measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(3, sum);
    delete s;
}
TEST(test_qadd_2c, reverse_qadd_negative_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 14;
    b = 11;
    StateVector* s = new StateVector(bits + 2);
    // кодируем слагаемые в состоянии системы
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            s->x(bits - 1 - i);
        b /= 2;
    }
    s->x(4);
    s->x(5);
    // к слагаемому a необходимо применить КПФ
    s->qft(0, bits, false);
    // схема квантового сложения
    s->iqadd_2c(a, 4, 5, 0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    s->iqft(0, bits, false);
    // измеряем состояние системы
    unsigned res = s->measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(13, sum);
    delete s;
}

TEST(test_qaddMod, can_apply) {
    StateVector* s = new StateVector(8);
    ASSERT_NO_THROW(s->qaddMod_2c(3, 6, 0, 1, 2, 4, false));
    delete s;
}
TEST(test_qaddMod, can_apply_approximate) {
    StateVector* s = new StateVector(8);
    ASSERT_NO_THROW(s->qaddMod_2c(3, 6, 0, 1, 2, 4, true));
    delete s;
}
TEST(test_qaddMod, control_qubit_in_zero_state) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(2, 3, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_2) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(1, 3, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_3) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(1, 2, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_4) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(2, 3, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(2, 3, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_2_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(1, 3, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_3_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(1, 2, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, control_qubit_in_zero_state_4_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->qaddMod_2c(2, 3, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_qaddMod, _13_plus_10_mod_14) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);
    s->x(4);
    s->x(6);

    s->qft(2, 7, false);
    s->qaddMod_2c(10, 14, 0, 1, 2, 4, false);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 3) + (1 << 6);

    EXPECT_EQ(expected, actual);
}
TEST(test_qaddMod, _8_plus_9_mod_11) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);

    s->qft(2, 7, false);
    s->qaddMod_2c(9, 11, 0, 1, 2, 4, false);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 4) + (1 << 5);

    EXPECT_EQ(expected, actual);
}
TEST(test_qaddMod, _13_plus_10_mod_14_approximate) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);
    s->x(4);
    s->x(6);

    s->qft(2, 7, false);
    s->qaddMod_2c(10, 14, 0, 1, 2, 4, true);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 3) + (1 << 6);

    EXPECT_EQ(expected, actual);
}
TEST(test_qaddMod, _8_plus_9_mod_11_approximate) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);

    s->qft(2, 7, false);
    s->qaddMod_2c(9, 11, 0, 1, 2, 4, true);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 4) + (1 << 5);

    EXPECT_EQ(expected, actual);
}

TEST(test_iqaddMod, can_apply) {
    StateVector* s = new StateVector(8);
    ASSERT_NO_THROW(s->iqaddMod_2c(3, 6, 0, 1, 2, 4, false));
    delete s;
}
TEST(test_iqaddMod, can_apply_approximate) {
    StateVector* s = new StateVector(8);
    ASSERT_NO_THROW(s->iqaddMod_2c(3, 6, 0, 1, 2, 4, true));
    delete s;
}
TEST(test_iqaddMod, control_qubit_in_zero_state) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(2, 3, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_2) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(1, 3, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_3) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(1, 2, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_4) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(2, 3, 0, 1, 2, 2, false);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(2, 3, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_2_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(3);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(3);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(1, 3, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_3_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(1, 2, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, control_qubit_in_zero_state_4_approximate) {
    StateVector* s1 = new StateVector(6);
    StateVector* s2 = new StateVector(6);

    s1->x(0);
    s1->x(4);
    s1->qft(2, 5, false);
    s2->x(0);
    s2->x(4);
    s2->qft(2, 5, false);

    s1->iqaddMod_2c(2, 3, 0, 1, 2, 2, true);

    vector<Complex> expected = s2->getState(), actual = s1->getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
    delete s1;
    delete s2;
}
TEST(test_iqaddMod, _13_minus_10_mod_14) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);
    s->x(4);
    s->x(6);

    s->qft(2, 7, false);
    s->iqaddMod_2c(10, 14, 0, 1, 2, 4, false);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 5) + (1 << 6);

    EXPECT_EQ(expected, actual);
}
TEST(test_iqaddMod, _8_minus_9_mod_11) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);

    s->qft(2, 7, false);
    s->iqaddMod_2c(9, 11, 0, 1, 2, 4, false);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 3) + (1 << 5);

    EXPECT_EQ(expected, actual);
}
TEST(test_iqaddMod, _13_minus_10_mod_14_approximate) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);
    s->x(4);
    s->x(6);

    s->qft(2, 7, false);
    s->iqaddMod_2c(10, 14, 0, 1, 2, 4, true);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 5) + (1 << 6);

    EXPECT_EQ(expected, actual);
}
TEST(test_iqaddMod, _8_minus_9_mod_11_approximate) {
    StateVector* s = new StateVector(8);

    s->x(0);
    s->x(1);
    s->x(3);

    s->qft(2, 7, false);
    s->iqaddMod_2c(9, 11, 0, 1, 2, 4, true);
    s->iqft(2, 7, false);

    size_t actual = s->measure();
    delete s;
    size_t expected = 1 + (1 << 1) + (1 << 3) + (1 << 5);

    EXPECT_EQ(expected, actual);
}