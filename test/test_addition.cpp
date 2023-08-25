//
// Created by Алексей on 13.07.2023.
//

#include "Addition.h"
#include "gtest.h"
#include "System.h"

/*
TEST(test_addition, classic_3bit_circuit) {
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

TEST(test_addition, classic) {
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
*/
TEST(qft, can_apply_qadd_circuit) {
    System s(7);
    Circuit circ(7);
    circ.qadd(0, 3);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qft, can_apply_iqadd_circuit) {
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

TEST(test_addition, quantum) {
    EXPECT_EQ(3, quantumAdd(1, 2, 4));
    EXPECT_EQ(3, quantumAdd(0, 3, 2));
    EXPECT_EQ(0, quantumAdd(1, 3, 2));
    EXPECT_EQ(1, quantumAdd(4, 5, 3));
    EXPECT_EQ(3, quantumAdd(5, 6, 3));
    EXPECT_EQ(3, quantumAdd(4, 7, 3));
    EXPECT_EQ(6, quantumAdd(7, 7, 3));
    EXPECT_EQ(2, quantumAdd(4, 6, 3));
    EXPECT_EQ(6, quantumAdd(2, 4, 3));
    EXPECT_EQ(11, quantumAdd(12, 15, 4));
    EXPECT_EQ(2, quantumAdd(11, 7, 4));
    // EXPECT_EQ(28, quantumAdd(31, 29, 5));
    //EXPECT_EQ(27, quantumAdd(28, 31, 5));
}
TEST(test_addition, quantum_approximate) {
    EXPECT_EQ(3, quantumAdd(1, 2, 2, true));
    EXPECT_EQ(3, quantumAdd(0, 3, 2, true));
    EXPECT_EQ(0, quantumAdd(1, 3, 2, true));
    EXPECT_EQ(1, quantumAdd(4, 5, 3, true));
    EXPECT_EQ(3, quantumAdd(5, 6, 3, true));
    EXPECT_EQ(3, quantumAdd(4, 7, 3, true));
    EXPECT_EQ(6, quantumAdd(7, 7, 3, true));
    EXPECT_EQ(2, quantumAdd(4, 6, 3, true));
    EXPECT_EQ(6, quantumAdd(2, 4, 3, true));
    EXPECT_EQ(11, quantumAdd(12, 15, 4, true));
    EXPECT_EQ(2, quantumAdd(11, 7, 4, true));
    // EXPECT_EQ(28, quantumAdd(31, 29, 5, true));
    // EXPECT_EQ(27, quantumAdd(28, 31, 5, true));
}
TEST(test_addition, reverse_qadd_positive_sum) {
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
TEST(test_addition, reverse_qadd_negative_sum) {
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
    init->h(4);
    init->h(5);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 2, 0, 1, 0, 2, false);
    s1.apply(*circ);
    delete circ;

    Circuit* tmp = new Circuit(9);
    tmp->x(1);
    s2.apply(*tmp);
    delete tmp;

    EXPECT_EQ(s2.getState(), s1.getState());
}
TEST(test_qaddMod, control_qubit_in_zero_state_approximate) {
    System s1(9), s2(9);

    Circuit* init = new Circuit(9);
    init->x(0);
    init->h(4);
    init->h(5);
    s1.apply(*init);
    s2.apply(*init);
    delete init;

    Circuit* circ = new Circuit(9);
    circ->qaddMod_2c(2, 2, 0, 1, 0, 2, true);
    s1.apply(*circ);
    delete circ;

    Circuit* tmp = new Circuit(9);
    tmp->x(1);
    s2.apply(*tmp);
    delete tmp;

    EXPECT_EQ(s2.getState(), s1.getState());
}