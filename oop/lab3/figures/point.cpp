#include "point.h"

namespace lab3 {

Point operator+(const Point &p1, const Point &p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}

Point operator-(const Point &p) {
    return Point{-p.x, -p.y};
}

Point operator-(const Point &p1, const Point &p2) {
    return p1 + (-p2);
}

Point operator*(const Point &p, const double x) {
    return Point{p.x * x, p.y * x};
}

Point operator*(const double x, const Point &p) {
    return p * x;
}

bool operator==(const Point &p1, const Point &p2) {
    return (std::abs(p1.x - p2.x) < EPS) && (std::abs(p1.y - p2.y) < EPS);
}

bool operator<(const Point &p1, const Point &p2) {
    if (p1.x == p2.x) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}

std::ostream& operator<<(std::ostream &stream, const Point &p) {
    stream << "Point(" << p.x << ", " << p.y << ")";
    return stream;
}

std::istream& operator>>(std::istream &stream, Point &p) {
    std::cin >> p.x >> p.y;
    return stream;
}

} // namespace lab3
