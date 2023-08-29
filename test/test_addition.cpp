//
// Created by Алексей on 13.07.2023.
//

#include "Addition.h"
#include "gtest.h"
#include "System.h"

/*
TEST(add, classic_3bit_circuit) {
    System s{10};

    Circuit init(10);
    init.x(2);
    init.x(7);
    init.x(8);
    s.apply(init);

    Circuit circ(10);
    circ.add(3);

    s.apply(circ);
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
}
 */
TEST(qadd, reverse_qadd_positive_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 11;
    b = 14;
    System s(2 * bits);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2 * bits);
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            init->x(2 * bits - 1 - i);
        b /= 2;
        if (a % 2 == 1)
            init->x(bits - 1 - i);
        a /= 2;
    }
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2 * bits);
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, false);
    // схема квантового сложения
    circ->iqadd(0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, false);
    s.apply(*circ);
    delete circ;
    // измеряем состояние системы
    unsigned res = s.measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    res = res >> bits;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(3, sum);
}
TEST(qadd, reverse_qadd_negative_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 14;
    b = 11;
    System s(2 * bits);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2 * bits);
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            init->x(2 * bits - 1 - i);
        b /= 2;
        if (a % 2 == 1)
            init->x(bits - 1 - i);
        a /= 2;
    }
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2 * bits );
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, false);
    // схема квантового сложения
    circ->iqadd(0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, false);
    s.apply(*circ);
    delete circ;
    // измеряем состояние системы
    unsigned res = s.measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    res = res >> bits;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(13, sum);
}

TEST(test_qadd_1c, control_qubit_in_zero_state) {
    System s1(9), s2(9);
    Circuit* init = new Circuit(9);
    init->x(1);
    init->x(3);
    init->h(5);
    init->h(8);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qadd_1c(0, 1, 4, false);
    s1.apply(*circ);
    delete circ;

    EXPECT_EQ(s2.getState(), s1.getState());
}
/*
TEST(test_qadd_1c, addition) {
    EXPECT_EQ(3, quantumAdd_1c(1, 2, 3));
    EXPECT_EQ(3, quantumAdd_1c(0, 3, 2));
    EXPECT_EQ(0, quantumAdd_1c(1, 3, 2));
    EXPECT_EQ(1, quantumAdd_1c(4, 5, 3));
    EXPECT_EQ(3, quantumAdd_1c(5, 6, 3));
    EXPECT_EQ(3, quantumAdd_1c(4, 7, 3));
    EXPECT_EQ(6, quantumAdd_1c(7, 7, 3));
}
 */
TEST(test_qadd_1c, qadd_is_inverse_to_iqadd) {
    System s1(7), s2(7);
    Circuit init(7);
    init.h(0);
    init.x(1);
    init.y(2);
    init.h(2);
    init.z(2);
    init.x(6);
    s1.apply(init);
    s2.apply(init);

    Circuit circ(7);
    circ.qadd_1c(6, 0, 3);
    circ.iqadd_1c(6, 0, 3);

    s1.apply(circ);

    vector<Complex> expected, actual;
    expected = s2.getState();
    actual = s1.getState();

    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
    }
}

TEST(test_qadd_2c, control_qubit_in_zero_state) {
    System s1(8), s2(8);
    Circuit* init = new Circuit(8);
    init->x(1);
    init->x(3);
    init->h(5);
    init->h(6);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(8);
    circ->qadd_2c(0, 1, 2, 3, false);
    s1.apply(*circ);
    delete circ;

    EXPECT_EQ(s2.getState(), s1.getState());
}
TEST(test_iqadd_2c, control_qubit_in_zero_state) {
    System s1(8), s2(8);
    Circuit* init = new Circuit(8);
    init->x(1);
    init->x(3);
    init->h(5);
    init->h(6);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(8);
    circ->iqadd_2c(0, 1, 2, 3, false);
    s1.apply(*circ);
    delete circ;

    EXPECT_EQ(s2.getState(), s1.getState());
}
/*
TEST(test_qadd_2c, quantum) {
    EXPECT_EQ(3, quantumAdd_2c(1, 2, 3));
    EXPECT_EQ(3, quantumAdd_2c(0, 3, 2));
    EXPECT_EQ(0, quantumAdd_2c(1, 3, 2));
    EXPECT_EQ(1, quantumAdd_2c(4, 5, 3));
    EXPECT_EQ(3, quantumAdd_2c(5, 6, 3));
    EXPECT_EQ(3, quantumAdd_2c(4, 7, 3));
    EXPECT_EQ(6, quantumAdd_2c(7, 7, 3));
}
 */
TEST(test_qadd_2c, qadd_is_inverse_to_iqadd) {
    System s1(8), s2(8);
    Circuit init(8);
    init.h(0);
    init.x(1);
    init.y(2);
    init.h(2);
    init.z(2);
    init.x(6);
    init.x(7);
    s1.apply(init);
    s2.apply(init);

    Circuit circ(8);
    circ.qadd_2c(6, 7, 0, 3);
    circ.iqadd_2c(6, 7, 0, 3);

    s1.apply(circ);

    vector<Complex> expected, actual;
    expected = s2.getState();
    actual = s1.getState();

    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
    }
}
TEST(test_qadd_2c, reverse_qadd_positive_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 11;
    b = 14;
    System s(2 * bits + 2);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2 * bits + 2);
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            init->x(2 * bits - 1 - i);
        b /= 2;
        if (a % 2 == 1)
            init->x(bits - 1 - i);
        a /= 2;
    }
    init->x(2*bits);
    init->x(2*bits + 1);
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2 * bits + 2);
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, false);
    // схема квантового сложения
    circ->iqadd_2c(2*bits, 2*bits + 1, 0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, false);
    s.apply(*circ);
    delete circ;
    // измеряем состояние системы
    unsigned res = s.measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    res = res >> bits;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(3, sum);
}
TEST(test_qadd_2c, reverse_qadd_negative_sum) {
    size_t bits = 4;
    unsigned a, b;
    a = 14;
    b = 11;
    System s(2 * bits + 2);
    // кодируем слагаемые в состоянии системы
    Circuit* init = new Circuit(2 * bits + 2);
    for (int i = 0; i < bits; i++) {
        if (b % 2 == 1)
            init->x(2 * bits - 1 - i);
        b /= 2;
        if (a % 2 == 1)
            init->x(bits - 1 - i);
        a /= 2;
    }
    init->x(2*bits);
    init->x(2*bits + 1);
    s.apply(*init);
    delete init;
    // применяем схему квантового сложения
    Circuit* circ = new Circuit(2 * bits + 2);
    // к слагаемому a необходимо применить КПФ
    circ->qft(bits, bits + bits, false);
    // схема квантового сложения
    circ->iqadd_2c(2*bits, 2*bits + 1,0, bits, false);
    // чтобы получить результат, необходимо обратное КПФ
    circ->iqft(bits, bits + bits, false);
    s.apply(*circ);
    delete circ;
    // измеряем состояние системы
    unsigned res = s.measure();
    // интерпретируем результат как сумму
    unsigned sum = 0;
    res = res >> bits;
    for (int i = 0; i < bits; i++) {
        sum = sum << 1;
        sum += res % 2;
        res = res >> 1;
    }
    EXPECT_EQ(13, sum);
}

TEST(test_qaddMod, can_apply) {
    System s(9);
    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 2, 0, 1, 0, 2, false);
    ASSERT_NO_THROW(s.apply(*circ));
    delete circ;
}
TEST(test_qaddMod, can_apply_approximate) {
    System s(9);
    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 2, 0, 1, 0, 2, true);
    ASSERT_NO_THROW(s.apply(*circ));
    delete circ;
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
