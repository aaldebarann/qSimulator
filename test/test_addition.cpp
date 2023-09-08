//
// Created by Алексей on 13.07.2023.
//

#include "Addition.h"
#include "gtest.h"
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
    EXPECT_EQ(109, classicalAdd(46, 63, 6));
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
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
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
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
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
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
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
    StateVector* s = new StateVector(6);
    ASSERT_NO_THROW(s->qaddMod_2c(3, 6, 0, 1, 2, 4, false));
    delete s;
}
TEST(test_qaddMod, can_apply_approximate) {
    StateVector* s = new StateVector(6);
    ASSERT_NO_THROW(s->qaddMod_2c(3, 6, 0, 1, 2, 4, true));
    delete s;
}
TEST(test_qaddMod, control_qubit_in_zero_state) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 3, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_2) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 3, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 2, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_4) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 3, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_approximate_2) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 3, 0, 1, 2, 2, true);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_approximate_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 2, 0, 1, 2, 2, true);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_approximate_4) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 3, 0, 1, 2, 2, true);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, control_qubit_in_zero_state_approximate) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 3, 0, 1, 2, 2, true);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_qaddMod, _0_plus_1_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_qaddMod, _1_plus_1_mod_2) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 2, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
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
TEST(test_qaddMod, _1_plus_2_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
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
TEST(test_qaddMod, _2_plus_1_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(1, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
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
TEST(test_qaddMod, _2_plus_2_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_qaddMod, _2_plus_3_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(3, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(6);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_qaddMod, _3_plus_6_mod_7) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(8);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->qaddMod_2c(6, 7, 0, 1, 2, 3, false);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
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
TEST(test_qaddMod, _5_plus_4_mod_7) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(7);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->qaddMod_2c(4, 7, 0, 1, 2, 3, false);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
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
TEST(test_qaddMod, _3_plus_6_mod_7_approximate) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(8);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->qaddMod_2c(6, 7, 0, 1, 2, 3, true);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
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
TEST(test_qaddMod, _5_plus_4_mod_7_approximate) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(7);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->qaddMod_2c(4, 7, 0, 1, 2, 3, true);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
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

TEST(test_iqaddMod, control_qubit_in_zero_state) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(2, 3, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_iqaddMod, control_qubit_in_zero_state_2) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(1, 3, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_iqaddMod, control_qubit_in_zero_state_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(1, 2, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_iqaddMod, control_qubit_in_zero_state_4) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(2, 3, 0, 1, 2, 2, false);
    s1.apply(*circ);
    delete circ;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}
TEST(test_iqaddMod, _0_minus_1_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(1, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(6);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _1_minus_1_mod_2) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(1, 2, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
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
TEST(test_iqaddMod, _1_minus_2_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(7);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(2, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(6);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _2_minus_1_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(1, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _2_minus_2_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(2, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
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
TEST(test_iqaddMod, _2_minus_3_mod_3) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->x(1);
    init->x(6);
    init->qft(5, 8, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->iqaddMod_2c(3, 3, 0, 1, 2, 2, false);
    circ->iqft(5, 8, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(9);
    expect->x(0);
    expect->x(1);
    expect->x(6);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _3_minus_6_mod_7) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(8);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->iqaddMod_2c(6, 7, 0, 1, 2, 3, false);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
    expect->x(0);
    expect->x(1);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _5_minus_4_mod_7) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(7);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->iqaddMod_2c(4, 7, 0, 1, 2, 3, false);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
    expect->x(0);
    expect->x(1);
    expect->x(9);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _3_minus_6_mod_7_approximate) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(8);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->iqaddMod_2c(6, 7, 0, 1, 2, 3, true);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
    expect->x(0);
    expect->x(1);
    expect->x(7);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
TEST(test_iqaddMod, _5_minus_4_mod_7_approximate) {
    System s1(11), s2(11);

    Circuit* init = new Circuit(11);
    init->x(0);
    init->x(1);
    init->x(7);
    init->x(9);
    init->qft(6, 10, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(11);
    circ->iqaddMod_2c(4, 7, 0, 1, 2, 3, true);
    circ->iqft(6, 10, false);
    s1.apply(*circ);
    delete circ;

    Circuit* expect = new Circuit(11);
    expect->x(0);
    expect->x(1);
    expect->x(9);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
/*
TEST(test_qaddMod, _13_plus_12_mod_15) {
    System s1(13), s2(13);

    Circuit* init = new Circuit(13);
    init->x(0);
    init->x(1);
    init->x(8);
    init->x(9);
    init->x(11);
    init->qft(7, 12, false);
    s1.apply(*init);
    delete init;

    Circuit* circ = new Circuit(13);
    circ->qaddMod_2c(12, 15, 0, 1, 2, 4, false);
    s1.apply(*circ);
    delete circ;

    Circuit* after = new Circuit(13);
    after->iqft(7, 12, false);
    s1.apply(*after);
    delete after;

    Circuit* expect = new Circuit(13);
    expect->x(0);
    expect->x(1);
    expect->x(3);
    expect->x(4);
    expect->x(8);
    expect->x(10);
    s2.apply(*expect);
    delete expect;

    vector<Complex> expected = s2.getState(), actual = s1.getState();
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-6);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-6);
    }
}
 */
