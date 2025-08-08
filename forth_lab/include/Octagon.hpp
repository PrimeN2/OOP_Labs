#pragma once
#include "Figure.hpp"

template <class T>
requires Scalar<T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center;
    T radius;
public:
    Octagon(T cx, T cy, T r) : center(std::make_unique<Point<T>>(cx, cy)), radius(r) {}
    double area() const override {
        return 2.0 * static_cast<double>(radius) * static_cast<double>(radius) * (1.0 + std::sqrt(2.0));
    }
    void printVertices() const override {
        std::cout << "Vertices of regular octagon with center (" << center->x << ", " << center->y
                  << ") and radius " << radius << std::endl;
    }
    void printCenter() const override {
        std::cout << "Center: (" << center->x << ", " << center->y << ")" << std::endl;
    }
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon<T>>(center->x, center->y, radius);
    }
    bool operator==(const Figure<T>& other) const override {
        if (auto ptr = dynamic_cast<const Octagon<T>*>(&other)) {
            return center->x == ptr->center->x && center->y == ptr->center->y && radius == ptr->radius;
        }
        return false;
    }
    explicit operator double() const override { return area(); }
};
