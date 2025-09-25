#include <gtest/gtest.h>
#include "closest_pair_tonum.h"

TEST(TaskTest, SmallNumTest) {
    Pair result = closest_pair_tonum(10);
    Pair expected = {5, 4};

    EXPECT_EQ(result, expected);
}

TEST(TaskTest, MidNumTest) {
    Pair result = closest_pair_tonum(30);
    Pair expected = {29, 20};

    EXPECT_EQ(result, expected);
}

TEST(TaskTest, LargeNumTest) {
    Pair result = closest_pair_tonum(50);
    Pair expected = {45, 36};

    EXPECT_EQ(result, expected);
}