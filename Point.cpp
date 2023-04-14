#include "Point.h"

Point::Point() : x{0}, y{0} {}

Point::Point(float x, float y) : x{x}, y{y} {}

float Point::getX() const { return x; }

float Point::getY() const { return y; }

void Point::setX(float x_) { this->x = x_; }

void Point::setY(float y_) { this->y = y_; }

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
