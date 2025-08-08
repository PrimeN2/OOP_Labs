#pragma once
#include "Figure.hpp"

template <class T>
requires Scalar<T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3;
public:
    Triangle(T x1, T y1, T x2, T y2, T x3, T y3)
        : p1(std::make_unique<Point<T>>(x1, y1)),
          p2(std::make_unique<Point<T>>(x2, y2)),
          p3(std::make_unique<Point<T>>(x3, y3)) {}
    double area() const override {
        return 0.5 * std::abs((p2->x - p1->x) * (p3->y - p1->y) - (p3->x - p1->x) * (p2->y - p1->y));
    }
    void printVertices() const override {
        std::cout << "Vertices: (" << p1->x << ", " << p1->y << "), ("
                  << p2->x << ", " << p2->y << "), ("
                  << p3->x << ", " << p3->y << ")" << std::endl;
    }
    void printCenter() const override {
        T cx = (p1->x + p2->x + p3->x) / static_cast<T>(3);
        T cy = (p1->y + p2->y + p3->y) / static_cast<T>(3);
        std::cout << "Center: (" << cx << ", " << cy << ")" << std::endl;
    }
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Triangle<T>>(p1->x, p1->y, p2->x, p2->y, p3->x, p3->y);
    }
    bool operator==(const Figure<T>& other) const override {
        if (auto ptr = dynamic_cast<const Triangle<T>*>(&other)) {
            return p1->x == ptr->p1->x && p1->y == ptr->p1->y &&
                   p2->x == ptr->p2->x && p2->y == ptr->p2->y &&
                   p3->x == ptr->p3->x && p3->y == ptr->p3->y;
        }
        return false;
    }
    explicit operator double() const override { return area(); }
};
