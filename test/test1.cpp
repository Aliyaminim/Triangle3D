#include "gtest/gtest.h"
#include "primitives.hpp"
#include "geotools.hpp"

TEST(TestClassPointt, TestValid) {
    Point_t p{};
    ASSERT_TRUE(std::isnan(p.x));
}

TEST(TestClassPointt, TestEqual1) {
    Point_t p1(35.3, 76.8, 93.0);
    Point_t p2(4858, 39339, 4939);
    ASSERT_FALSE(p1.equal_point(p2));
}

TEST(TestClassPointt, TestEqual2) {
    Point_t p1(35.3, 76.8, 93.0);
    Point_t p2(35.30001, 76.800001, 93.000001);
    ASSERT_TRUE(p1.equal_point(p2));
}

TEST(TestTrianglet, Testboundingboxesoverlap1) {
    Point_t p1(0, 0, 0);
    Point_t p2(0, 1, 0);
    Point_t p3(1, 0, 0);
    Triangle_t tr1{p1, p2, p3};

    Point_t p1_(0.4, 0.4, 0);
    Point_t p2_(0, 1, 0);
    Point_t p3_(0, 0.2, 0);
    Triangle_t tr2{p1_, p2_, p3_};

    ASSERT_TRUE(boundingboxes_overlap(tr1, tr2));
}

TEST(TestTrianglet, Testboundingboxesoverlap2) {
    Point_t p1(0, 0, 0);
    Point_t p2(0, 1, 0);
    Point_t p3(1, 0, 0);
    Triangle_t tr1{p1, p2, p3};

    Point_t p1_(2, 1, 0);
    Point_t p2_(4, 5, 6);
    Point_t p3_(10, 0, 34);
    Triangle_t tr2{p1_, p2_, p3_};

    ASSERT_FALSE(boundingboxes_overlap(tr1, tr2));
}