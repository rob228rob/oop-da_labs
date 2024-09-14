// Восьмиугольник, треугольник, квадрат

#pragma once

#include "point.h"

#include <algorithm>

namespace lab3 {

class Figure {
public:
    virtual Point geometricCenter() const = 0;
    virtual operator double () const = 0; 
};

class Octagon : public Figure {
private:
    Point point1, point2;
    int orientation; // Either 1 or -1
public:
    Octagon() = default;
    Octagon(const Point& point1, const Point& point2, int orientation);
    Octagon(const Octagon &oct);
    Octagon(Octagon &&oct);

    Octagon& operator=(const Octagon &oct);
    Octagon& operator=(Octagon &&oct);
    
    bool operator==(const Octagon &other);

    operator double () const override;
    Point geometricCenter() const override;

    friend std::ostream& operator<<(std::ostream &stream, const Octagon &sq);
    friend std::istream& operator>>(std::istream &stream, Octagon &sq);  
};

class Triangle : public Figure {
private:
    Point point1, point2;
    int orientation; // Either 1 or -1
public:
    Triangle() = default;
    Triangle(const Point& point1, const Point& point2, int orientation);
    Triangle(const Triangle &tr);
    Triangle(Triangle &&tr);
    
    Triangle& operator=(const Triangle &tr);
    Triangle& operator=(Triangle &&tr);

    bool operator==(const Triangle &other);

    operator double () const override;
    Point geometricCenter() const override;

    friend std::ostream& operator<<(std::ostream &stream, const Triangle &sq);
    friend std::istream& operator>>(std::istream &stream, Triangle &sq);   
};

class Square : public Figure {
private:
    // Two opposite points
    Point point1, point2;
public:
    Square() = default;
    Square(const Point& point1, const Point& point2);
    Square(const Square &sq);
    Square(Square &&sq);
    
    Square& operator=(const Square &sq);
    Square& operator=(Square &&sq);

    bool operator==(const Square &other);

    operator double () const override;
    Point geometricCenter() const override;

    friend std::ostream& operator<<(std::ostream &stream, const Square &sq);
    friend std::istream& operator>>(std::istream &stream, Square &sq);
};

} // namespace lab3
