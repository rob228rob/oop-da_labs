#pragma once

#include "point.h"

namespace lab4 {

template<class T>
class Figure {
public:
    using Point = lab4::Point<T>;

    virtual Point geometricCenter() const = 0;
    virtual operator double () const = 0; 
};

template<Number T>
class Octagon : public Figure<T> {
private:
    Point<T> point1, point2;
    int orientation; // Either 1 or -1
public:
    Octagon() = default;
    
    Octagon(const Point<T>& point1, const Point<T>& point2, int orientation) {
        this->point1 = point1;
        this->point2 = point2;
        this->orientation = orientation;
    }

    Octagon(const Octagon &oct) {
        this->point1 = oct.point1;
        this->point2 = oct.point2;
        this->orientation = oct.orientation;
    }

    Octagon(Octagon &&oct) {
        point1 = oct.point1;
        point2 = oct.point2;
        orientation = oct.orientation;
    }

    Octagon& operator=(const Octagon &oct) {
        point1 = oct.point1;
        point2 = oct.point2;
        orientation = oct.orientation;
        return *this;
    }

    Octagon& operator=(Octagon &&oct) {
        point1 = oct.point1;
        point2 = oct.point2;
        orientation = oct.orientation;
        return *this;
    }
    
    bool operator==(const Octagon &other) {
        return point1 == other.point1 && point2 == other.point2 && orientation == other.orientation;
    }

    operator double () const override {
        return 2 * (sqrt(2) + 1) * std::pow(Point<T>::distance(point1, point2), 2);
    }

    Point<T> geometricCenter() const override {
        double r = Point<T>::distance(point1, point2) / 2 * (1 + sqrt(2));
        return Point<T>::mid(point1, point2) + r * Point<T>::rotate(Point<T>::normalize(point2 - point1), PI / 2  * orientation);
    }

    friend std::ostream& operator<<(std::ostream &stream, const Octagon &tr) {
        Point<T> side = tr.point2 - tr.point1;
        stream << "Octagon[ " << tr.point1 << " " << tr.point2 << " "; 
        Point<T> currentPoint = tr.point2;
        for (int i = 0; i < 6; i++) {
            side = Point<T>::rotate(side, 1. / 4 * PI * tr.orientation);
            currentPoint = currentPoint + side;
            stream << currentPoint << " ";
        }
        stream << "]";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Octagon &sq) {
        std::cout << "Input pair of figure coords and input orientation(1 or -1 only): \n"; 
        Point<T> p1, p2;
        int orientation;
        stream >> p1 >> p2 >> orientation;
        sq = Octagon<T>(p1, p2, orientation);
        return stream;
    }
};

template<Number T>
class Triangle : public Figure<T> {
private:
    Point<T> point1, point2;
    int orientation; // Either 1 or -1
public:
    Triangle() = default;

    Triangle(const Point<T>& point1, const Point<T>& point2, int orientation) {
        this->point1 = point1;
        this->point2 = point2;
        this->orientation = orientation;
    }

    Triangle(const Triangle &tr) {
        point1 = tr.point1;
        point2 = tr.point2;
        orientation = tr.orientation;
    }

    Triangle(Triangle &&tr) {
        point1 = tr.point1;
        point2 = tr.point2;
        orientation = tr.orientation;
    }

    Triangle& operator=(const Triangle &tr) {
        point1 = tr.point1;
        point2 = tr.point2;
        orientation = tr.orientation;
        return *this;
    }

    Triangle& operator=(Triangle &&tr) {
        point1 = tr.point1;
        point2 = tr.point2;
        orientation = tr.orientation;
        return *this;
    }
        
    bool operator==(const Triangle &other) {
        return point1 == other.point1 && point2 == other.point2 && orientation == other.orientation;
    }

    operator double () const override {
        return sqrt(3) / 4 * std::pow(Point<T>::distance(point1, point2), 2);
    }

    Point<T> geometricCenter() const override {
        Point<T> point3 = point2 + Point<T>::rotate(point2 - point1, 2 * PI / 3 * orientation);
        return Point<T>::mid(point1, point2) + (1. / 3.) * (point3 - Point<T>::mid(point1, point2));
    }

    friend std::ostream& operator<<(std::ostream &stream, const Triangle &tr) {
        Point<T> point3 = tr.point2 + Point<T>::rotate(tr.point2 - tr.point1, 2 * PI / 3 * tr.orientation);
        stream << "Triangle[ " << tr.point1 << " " << tr.point2 << " " << point3 << " ]";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Triangle &tr) {
        std::cout << "Input pair of figure coords and input orientation(1 or -1 only): \n"; 
        Point<T> p1, p2;
        int orientation;
        stream >> p1 >> p2 >> orientation;
        tr = Triangle<T>(p1, p2, orientation);
        return stream;
    }

};

template<Number T>
class Square : public Figure<T> {
private:
    // Two opposite points
    Point<T> point1, point2;
public:
    Square() = default;

    Square(const Point<T>& point1, const Point<T>& point2) {
        if (abs(abs(point1.x - point2.x) - abs(point1.y - point2.y)) >= EPS) {
            throw std::invalid_argument("Bad points.");
        }
        this->point1 = point1;
        this->point2 = point2;
    }

    Square(const Square &sq) {
        point1 = sq.point1;
        point2 = sq.point2;
    }

    Square(Square &&sq) {
        point1 = sq.point1;
        point2 = sq.point2;
    }
        
    Square& operator=(const Square &sq) {
        point1 = sq.point1;
        point2 = sq.point2;
        return *this;
    }

    Square& operator=(Square &&sq) {
        point1 = sq.point1;
        point2 = sq.point2;
        return *this;
    }

    bool operator==(const Square &other) {
        return point1 == other.point1 && point2 == other.point2;
    }

    operator double () const override {
        return std::pow(Point<T>::distance(point1, point2), 2) / 2;
    }

    Point<T> geometricCenter() const override {
        return Point<T>::mid(point1, point2);
    }

    friend std::ostream& operator<<(std::ostream &stream, const Square &sq) {
        double deltaX = sq.point2.x - sq.point1.x, deltaY = sq.point2.y - sq.point1.y;
        stream << "Square[ " << sq.point1 << " " << sq.point1 + Point<T>{deltaX, 0} << " " <<
                sq.point1 + Point<T>{0, deltaY} << " " << sq.point2 << " ]";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Square &sq) {
        std::cout << "Input pair of figure coords: \n"; 
        Point<T> p1, p2;
        stream >> p1 >> p2;
        sq = Square<T>(p1, p2);
        return stream;
    }

};

}
