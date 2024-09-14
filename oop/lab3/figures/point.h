// Восьмиугольник, треугольник, квадрат

#pragma once

#include <iostream>
#include <vector>
#include <cmath>

namespace lab3 {

inline const double EPS = 1e-6;

inline const double PI = 3.14159265358979323846;

struct Point {
    double x, y;

    static double distance(const Point &p1, const Point &p2) {
        return std::sqrt(std::pow(p2.x - p1.x, 2) +
                         std::pow(p2.y - p1.y, 2));
    }

    static double distance(const Point &p) {
        return distance(Point{0, 0}, p);
    }

    static Point mid(const Point &p1, const Point &p2) {
        return Point{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    }

    static Point rotate(const Point &p, const double angle) {
        return Point{p.x * cos(angle) - p.y * sin(angle), 
                     p.x * sin(angle) + p.y * cos(angle)};
    }

    static Point normalize(const Point &p) {
        double den = distance(p);
        return Point{p.x / den, p.y / den};
    }
};

Point operator+(const Point &p1, const Point &p2);
Point operator-(const Point &p);
Point operator-(const Point &p1, const Point &p2);
Point operator*(const Point &p, const double x);
Point operator*(const double x, const Point &p);
bool operator==(const Point &p1, const Point &p2);
bool operator<(const Point &p1, const Point &p2);
std::ostream& operator<<(std::ostream &stream, const Point &p);
std::istream& operator>>(std::istream &stream, Point &p);

} // namespace lab3
