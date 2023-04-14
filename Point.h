#pragma once

#include <iostream>

class Point {
    float x;
    float y;

public:
    /// constructor + destructor
    Point();
    Point(float x, float y);
    ~Point() = default;

    /// getters + setters
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    void setX(float x_);
    void setY(float y_);

    /// cc
    Point(const Point& other) = default;

    /// operator=
    Point& operator=(const Point& other) = default;

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};
