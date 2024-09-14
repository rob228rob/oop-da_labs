#pragma once

#include <concepts>
#include <iostream>
#include <cmath>

namespace lab4 {

inline const double EPS = 1e-6;
inline const double PI = 3.14159265358979323846;

template<typename T>
concept Number = std::is_convertible_v<T, double>;

template<Number T>
struct Point {
    T x, y;

    Point(T _x, T _y) : x(_x), y(_y) { }
    Point() : x(0), y(0) { }

    Point(const Point &other) = default;
    Point(Point &&other) = default;

    Point& operator= (const Point &other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    Point& operator= (const Point &&other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << "Point(" << point.x << ", " << point.y << ")";
        return out;
    }

    friend std::istream& operator>>(std::istream &in, Point &point) {
        in >> point.x >> point.y;
        return in;
    }

    // =============================== //
    //  STATIC                         //
    // =============================== //

    static double distance(const Point &a, const Point &b) {
        double x1 = static_cast<double>(a.x),
               y1 = static_cast<double>(a.y),
               x2 = static_cast<double>(b.x),
               y2 = static_cast<double>(b.y);
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }

    static double distance(const Point &p) {
        return distance(Point<T>(0, 0), p);
    }

    static Point mid(const Point &p1, const Point &p2) {
        double x1 = static_cast<double>(p1.x),
               y1 = static_cast<double>(p1.y),
               x2 = static_cast<double>(p2.x),
               y2 = static_cast<double>(p2.y);
        return Point{T((x1 + x2) / 2), T((y1 + y2) / 2)};
    }

    static Point rotate(const Point &p, const double angle) {
        double x = static_cast<double>(p.x),
               y = static_cast<double>(p.y);
        return Point{T(x * cos(angle) - y * sin(angle)), 
                     T(x * sin(angle) + y * cos(angle))};
    }

    static Point normalize(const Point &p) {
        double den = distance(p);
        double x = static_cast<double>(p.x),
               y = static_cast<double>(p.y);
        return Point{T(x / den), T(y / den)};
    }

};

template<Number T>
Point<T> operator+(const Point<T> &lhs, const Point<T> &rhs) {
    return Point<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<Number T>
Point<T> operator-(const Point<T> &p) {
    return Point<T>(-p.x, -p.y);
}

template<Number T>
Point<T> operator-(const Point<T> &lhs, const Point<T> &rhs) {
    return lhs + (-rhs);
}

template<Number T, Number U>
Point<T> operator*(const Point<T> &p, U value) {
    return Point<T>(p.x * value, p.y * value);
}

template<Number T, Number U>
Point<T> operator*(U value, const Point<T> &p) {
    return p * value;
}

template<Number T>
bool operator==(const Point<T> &p1, const Point<T> &p2) {
    double x1 = static_cast<double>(p1.x),
           y1 = static_cast<double>(p1.y),
           x2 = static_cast<double>(p2.x),
           y2 = static_cast<double>(p2.y);
    return (std::abs(p1.x - p2.x) < EPS) && (std::abs(p1.y - p2.y) < EPS);
}

};
