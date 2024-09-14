#include "figures.h"

namespace lab3 {

// Figure

// Octagon

Octagon::Octagon(const Point& point1, const Point& point2, int orientation) {
    if ((orientation != 1) && (orientation != -1)) {
        throw std::invalid_argument("Invalid orientation. Orientation is either 1 or -1.");
    }
    this->point1 = point1;
    this->point2 = point2;
    this->orientation = orientation;
}

Octagon::Octagon(const Octagon &oct) {
    point1 = oct.point1;
    point2 = oct.point2;
    orientation = oct.orientation;
}

Octagon::Octagon(Octagon &&oct) {
    point1 = oct.point1;
    point2 = oct.point2;
    orientation = oct.orientation;
}

Octagon& Octagon::operator=(const Octagon &oct) {
    point1 = oct.point1;
    point2 = oct.point2;
    orientation = oct.orientation;
    return *this;
}

Octagon& Octagon::operator=(Octagon &&oct) {
    point1 = oct.point1;
    point2 = oct.point2;
    orientation = oct.orientation;
    return *this;
}
    
bool Octagon::operator==(const Octagon &other) {
    return point1 == other.point1 && point2 == other.point2 && orientation == other.orientation;
}

Octagon::operator double () const {
    return 2 * (sqrt(2) + 1) * std::pow(Point::distance(point1, point2), 2);
}

Point Octagon::geometricCenter() const {
    double r = Point::distance(point1, point2) / 2 * (1 + sqrt(2));
    return Point::mid(point1, point2) + r * Point::rotate(Point::normalize(point2 - point1), PI / 2  * orientation);
}

std::ostream& operator<<(std::ostream &stream, const Octagon &tr) {
    Point side = tr.point2 - tr.point1;
    stream << "Octagon[ " << tr.point1 << " " << tr.point2 << " "; 
    Point currentPoint = tr.point2;
    for (int i = 0; i < 6; i++) {
        side = Point::rotate(side, 1. / 4 * PI * tr.orientation);
        currentPoint = currentPoint + side;
        stream << currentPoint << " ";
    }
    stream << "]";
    return stream;
}

std::istream& operator>>(std::istream &stream, Octagon &tr) {
    std::cout << "Input 2 points of figure and orientation: \n"; 
    Point p1, p2;
    int orientation;
    stream >> p1 >> p2 >> orientation;
    tr = Octagon(p1, p2, orientation);
    return stream;
}


// Triangle

Triangle::Triangle(const Point& point1, const Point& point2, int orientation) {
    this->point1 = point1;
    this->point2 = point2;
    this->orientation = orientation;
}

Triangle::Triangle(const Triangle &tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    orientation = tr.orientation;
}

Triangle::Triangle(Triangle &&tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    orientation = tr.orientation;
}

Triangle& Triangle::operator=(const Triangle &tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    orientation = tr.orientation;
    return *this;
}

Triangle& Triangle::operator=(Triangle &&tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    orientation = tr.orientation;
    return *this;
}
    
bool Triangle::operator==(const Triangle &other) {
    return point1 == other.point1 && point2 == other.point2 && orientation == other.orientation;
}

Triangle::operator double () const {
    return sqrt(3) / 4 * std::pow(Point::distance(point1, point2), 2);
}

Point Triangle::geometricCenter() const {
    Point point3 = point2 + Point::rotate(point2 - point1, 2 * PI / 3 * orientation);
    return Point::mid(point1, point2) + (1. / 3.) * (point3 - Point::mid(point1, point2));
}

std::ostream& operator<<(std::ostream &stream, const Triangle &tr) {
    Point point3 = tr.point2 + Point::rotate(tr.point2 - tr.point1, 2 * PI / 3 * tr.orientation);
    stream << "Triangle[ " << tr.point1 << " " << tr.point2 << " " << point3 << " ]";
    return stream;
}

std::istream& operator>>(std::istream &stream, Triangle &tr) {
    std::cout << "Input 2 point of figure and orientation (1 or -1): \n"; 
    Point p1, p2;
    int orientation;
    stream >> p1 >> p2 >> orientation;
    tr = Triangle(p1, p2, orientation);
    return stream;
}

// Square

Square::Square(const Point& point1, const Point& point2) {
    if (abs(abs(point1.x - point2.x) - abs(point1.y - point2.y)) >= EPS) {
        throw std::invalid_argument("Bad points.");
    }
    this->point1 = point1;
    this->point2 = point2;
}

Square::Square(const Square &sq) {
    point1 = sq.point1;
    point2 = sq.point2;
}

Square::Square(Square &&sq) {
    point1 = sq.point1;
    point2 = sq.point2;
}
    
Square& Square::operator=(const Square &sq) {
    point1 = sq.point1;
    point2 = sq.point2;
    return *this;
}

Square& Square::operator=(Square &&sq) {
    point1 = sq.point1;
    point2 = sq.point2;
    return *this;
}

bool Square::operator==(const Square &other) {
    return point1 == other.point1 && point2 == other.point2;
}

Square::operator double () const {
    return std::pow(Point::distance(point1, point2), 2) / 2;
}

Point Square::geometricCenter() const {
    return Point::mid(point1, point2);
}

std::ostream& operator<<(std::ostream &stream, const Square &sq) {
    double deltaX = sq.point2.x - sq.point1.x, deltaY = sq.point2.y - sq.point1.y;
    stream << "Square[ " << sq.point1 << " " << sq.point1 + Point{deltaX, 0} << " " <<
              sq.point1 + Point{0, deltaY} << " " << sq.point2 << " ]";
    return stream;
}

std::istream& operator>>(std::istream &stream, Square &sq) {
    std::cout << "Input 2 points of figure: \n"; 
    Point p1, p2;
    stream >> p1 >> p2;
    sq = Square(p1, p2);
    return stream;
}

} // namespace lab3
