//
// Created by aleksei on 08.08.2023.
//
#include "gtest.h"
#include "shor.h"

TEST(test_shor, prime_number_is_not_perfect_power) {
    EXPECT_EQ(0, perfectPower(2));
    EXPECT_EQ(0, perfectPower(7));
    EXPECT_EQ(0, perfectPower(19));
    EXPECT_EQ(0, perfectPower(541));
    EXPECT_EQ(0, perfectPower(7309));
}
TEST(test_shor, number_is_not_perfect_power) {
    EXPECT_EQ(0, perfectPower(6));
    EXPECT_EQ(0, perfectPower(12));
    EXPECT_EQ(0, perfectPower(1001));
    EXPECT_EQ(0, perfectPower(6144));
    EXPECT_EQ(0, perfectPower(25482));
}
TEST(test_shor, number_is_perfect_power) {
    EXPECT_EQ(2, perfectPower(4));
    EXPECT_EQ(8, perfectPower(64));
    EXPECT_EQ(7, perfectPower(16807));
    EXPECT_EQ(2, perfectPower(8192));
    EXPECT_EQ(27, perfectPower(19683));
}
TEST(test_shor, classic_version) {
    int a[] = {1011,561, 1105, 1729, 2465,
               2821};
    EXPECT_EQ(0, 1011 % shor_classic(1011));
    EXPECT_EQ(0, 561 % shor_classic(561));
    EXPECT_EQ(0, 1105 % shor_classic(1105));
    EXPECT_EQ(0, 1729 % shor_classic(1729));
    EXPECT_EQ(0, 2465 % shor_classic(2465));
    EXPECT_EQ(0, 2821 % shor_classic(2821));
}