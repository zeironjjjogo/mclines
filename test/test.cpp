#include "../include/diag.hpp"
#include <gtest/gtest.h>

TEST(calc_test, calc)
{
    diag_line expect = { { 0, 0 }, { 1, 2.f/3 } };
    diag_line expect1 = { { 1, 2.f/3 }, { 3.f/2, 1 } };
    float x = 0, y = 0;
    EXPECT_EQ(expect, calc(x, y));
    EXPECT_EQ(expect1, calc(x, y)) << calc(x, y);
}
