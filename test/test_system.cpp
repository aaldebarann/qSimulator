//
// Created by Алексей on 15.05.2023.
//

#include <gtest.h>
#include "System.h"

TEST(System, can_create) {
    ASSERT_NO_THROW(System s(3));
}
TEST(System, can_get_state) {
    System s(3);
    ASSERT_NO_THROW(s.getState());
}