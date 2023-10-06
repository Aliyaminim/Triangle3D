#include "gtest/gtest.h"
#include "primitives.hpp"

float flt_tolerance = 0.00001;

TEST(TestClassPointt, TestValid) {
    Point_t p{};
    ASSERT_TRUE(std::isnan(p.x));
}

TEST(TestClassPointt, TestEqual1) {
    Point_t p1(35.3, 76.8, 93.0);
    Point_t p2(4858, 39339, 4939);
    ASSERT_FALSE(p1.equal(p2));
}

TEST(TestClassPointt, TestEqual2) {
    Point_t p1(35.3, 76.8, 93.0);
    Point_t p2(35.30001, 76.800001, 93.000001);
    ASSERT_TRUE(p1.equal(p2));
}