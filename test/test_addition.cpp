//
// Created by Алексей on 13.07.2023.
//

#include "Addition.h"
#include "gtest.h"
#include "System.h"

TEST(test_addition, classic_3bit_circuit) {
    System s{10};

    Circuit init(10);
    init.x(2);
    init.x(7);
    init.x(8);
    s.apply(init);

    Circuit circ(10);
    circ.add_classic(3);

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

TEST(test_addition, quantum) {
    EXPECT_EQ(3, quantumAdd(1, 2, 2));
    EXPECT_EQ(3, quantumAdd(0, 3, 2));
    EXPECT_EQ(0, quantumAdd(1, 3, 2));
    EXPECT_EQ(1, quantumAdd(4, 5, 3));
    EXPECT_EQ(3, quantumAdd(5, 6, 3));
    EXPECT_EQ(3, quantumAdd(4, 7, 3));
    EXPECT_EQ(6, quantumAdd(7, 7, 3));
    EXPECT_EQ(2, quantumAdd(4, 6, 3));
    EXPECT_EQ(6, quantumAdd(2, 4, 3));
    EXPECT_EQ(28, quantumAdd(31, 29, 5));
    EXPECT_EQ(27, quantumAdd(28, 31, 5));
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
    EXPECT_EQ(4, quantumAdd(5, 7, 3, true));
    EXPECT_EQ(27, quantumAdd(28, 31, 5, true));
}