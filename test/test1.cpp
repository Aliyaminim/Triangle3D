#include "gtest/gtest.h"
#include "header.hpp"

TEST(TestClassPointt, TestValid) {
    Point_t p;
    ASSERT_TRUE(std::isnan(p.x));
}