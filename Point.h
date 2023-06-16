#pragma once

#include <iostream>

template<class T>
class Point {
    T x;
    T y;

public:
    /// constructor + destructor
    Point();
    Point(T x, T y);
    ~Point() = default;

    /// getters + setters
    [[nodiscard]] T getX() const;
    [[nodiscard]] T getY() const;

    [[maybe_unused]] void setX(T x_);
    void setY(T y_);

    /// cc
    Point(const Point& other) = default;

    /// operator=
    Point& operator=(const Point& other) = default;

    /// operator<<
    template<class U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& point);
};

#include "Point.cpp"