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
    circ.add(3);

    s.apply(circ);
    size_t res = s.measure();
    std::cout << res << std::endl;
}

TEST(test_addition, classic) {
    EXPECT_EQ(3, classicalAdd(1, 2, 2));
    EXPECT_EQ(3, classicalAdd(0, 3, 2));
    EXPECT_EQ(4, classicalAdd(1, 3, 2));
    EXPECT_EQ(9, classicalAdd(4, 5, 3));
    EXPECT_EQ(11, classicalAdd(5, 6, 3));
    EXPECT_EQ(11, classicalAdd(4, 7, 3));
    EXPECT_EQ(14, classicalAdd(7, 7, 3));
    EXPECT_EQ(12, classicalAdd(4, 8, 4));
    EXPECT_EQ(23, classicalAdd(10, 13, 4));
    EXPECT_EQ(29, classicalAdd(14, 15, 4));
}