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

TEST(test_addition, qqq1) {
    std::map<int, int> m;
    for (int i = 0; i < 1000; i++) {
        int res = quantumAdd(1, 1, 2);
        auto x = m.find(res);
        if(x != m.end())
            x->second++;
        else
            m.insert({res, 1});
    }
    for(auto p: m) {
        std::cout << p.first << ":  "<<p.second<<std::endl;
    }
}
TEST(test_addition, qqq2) {
    std::map<int, int> m;
    for (int i = 0; i < 100; i++) {
        int res = quantumAdd(4, 5, 3);
        auto x = m.find(res);
        if (x != m.end())
            x->second++;
        else
            m.insert({res, 1});
    }
    for (auto p: m) {
        std::cout <<"\""<< p.first <<"\"" << ":  " << p.second << std::endl;
    }
}