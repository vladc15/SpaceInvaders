
template<class T>
Point<T>::Point() : x{0}, y{0} {}

template<class T>
Point<T>::Point(T x, T y) : x{x}, y{y} {}

template<class T>
T Point<T>::getX() const { return x; }

template<class T>
T Point<T>::getY() const { return y; }

template<class T>
[[maybe_unused]] void Point<T>::setX(T x_) { this->x = x_; }

template<class T>
void Point<T>::setY(T y_) { this->y = y_; }

template<class T>
std::ostream &operator<<(std::ostream &os, const Point<T> &point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
