#include <gtest/gtest.h>

#include "figures/figures.h"
#include "figures/array.h"

#include <iostream>
#include <sstream>

using namespace lab3;

TEST(FiguresTest, SquareTest) {
    double expectedArea = 9;
    Point expectedCenter = Point{1.5, 1.5};
    Square a = Square({0, 0}, {3, 3});
    EXPECT_TRUE(static_cast<double>(a) - expectedArea < EPS);
    EXPECT_EQ(a.geometricCenter(), expectedCenter);
}

TEST(FiguresTest, TriangleTest) {
    double expectedArea = 1.7320508075688772;
    Point expectedCenter = Point{1.57735, 0};
    Triangle a = Triangle({1, 1}, {1, -1}, 1);
    EXPECT_TRUE(static_cast<double>(a) - expectedArea < EPS);
    EXPECT_EQ(a.geometricCenter(), expectedCenter);
}

TEST(FiguresTest, OctagonTest) {
    double expectedArea = 43.45584;
    Point expectedCenter = Point{2.5, 0.792893};
    Octagon a = Octagon({2, 2}, {3, 2}, -1);
    EXPECT_TRUE(static_cast<double>(a) - expectedArea < EPS);
    EXPECT_EQ(a.geometricCenter(), expectedCenter);
}

TEST(FiguresTest, PointTest) {
    Point a{1, 1}, b{4, 5};
    EXPECT_TRUE(Point::distance(a, b) - 5 < EPS);
    Point expd = Point{2.5, 3};
    EXPECT_EQ(Point::mid(a, b), expd);
    Point c{3, 4};
    expd = Point{3. / 5, 4. / 5};
    EXPECT_EQ(Point::normalize(c), expd);
    expd = Point{0, 1};
    a = Point{1, 0};
    EXPECT_EQ(Point::rotate(a, PI/2), expd);
}

TEST(FiguresTest, ArrayTest) {
    Array array;
    Octagon a = Octagon({2, 2}, {3, 2}, -1);
    Triangle b = Triangle({1, 1}, {1, -1}, 1);
    Square c = Square({0, 0}, {3, 3});
    Figure *f1 = &a,
           *f2 = &b,
           *f3 = &c;
    array.pushBack(f1);
    array.pushBack(f2);
    array.pushBack(f3);
    EXPECT_EQ(array.size(), 3);
    array.resize(1000);
    EXPECT_EQ(array.size(), 1000);
    array.erase(1);
    EXPECT_EQ(array.size(), 999);
    EXPECT_EQ(array[1], f3);
}

