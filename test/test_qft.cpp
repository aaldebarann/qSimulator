//
// Created by Алексей on 21.07.2023.
//

#include "gtest.h"
#include "System.h"

TEST(qft, can_apply_qft_circuit) {
    System s(3);
    Circuit circ(3);
    circ.qft(0, 3);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qft, can_apply_iqft_circuit) {
    System s(3);
    Circuit circ(3);
    circ.iqft(0, 3);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qft, qft_is_inverse_to_iqft) {
    System s1(3), s2(3);
    Circuit init(3);
    init.h(0);
    init.x(1);
    init.y(2);
    init.h(2);
    init.z(2);
    s1.apply(init);
    s2.apply(init);

    Circuit circ(3);
    circ.qft(0, 3);
    circ.iqft(0, 3);

    s1.apply(circ);

    vector<Complex> expected, actual;
    expected = s2.getState();
    actual = s1.getState();

    for(int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
    }
}
TEST(qft, can_apply_approximate_qft_circuit) {
    System s(3);
    Circuit circ(3);
    circ.qft(0, 3, true);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qft, can_apply_approximate_iqft_circuit) {
    System s(3);
    Circuit circ(3);
    circ.iqft(0, 3, true);

    ASSERT_NO_THROW(s.apply(circ));
}
TEST(qft, approximate_qft_is_inverse_to_approximate_iqft) {
    System s1(3), s2(3);
    Circuit init(3);
    init.h(0);
    init.x(1);
    init.y(2);
    init.h(2);
    init.z(2);
    s1.apply(init);
    s2.apply(init);

    Circuit circ(3);
    circ.qft(0, 3, true);
    circ.iqft(0, 3, true);

    s1.apply(circ);

    vector<Complex> expected, actual;
    expected = s2.getState();
    actual = s1.getState();

    for(int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(expected[i].real(), actual[i].real(), 1.0e-7);
        EXPECT_NEAR(expected[i].imag(), actual[i].imag(), 1.0e-7);
    }
}