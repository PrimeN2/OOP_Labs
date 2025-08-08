#pragma once
#include "Figure.hpp"

template <class T>
requires Scalar<T>
class Square : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center;
    T side;
public:
    Square() : center(std::make_unique<Point<T>>(0, 0)), side(0) {}
    Square(T cx, T cy, T s) : center(std::make_unique<Point<T>>(cx, cy)), side(s) {}
    double area() const override { return static_cast<double>(side) * static_cast<double>(side); }
    void printVertices() const override {
        T half = side / static_cast<T>(2);
        std::cout << "Vertices: (" << center->x - half << ", " << center->y - half << "), ("
                  << center->x + half << ", " << center->y - half << "), ("
                  << center->x + half << ", " << center->y + half << "), ("
                  << center->x - half << ", " << center->y + half << ")" << std::endl;
    }
    void printCenter() const override {
        std::cout << "Center: (" << center->x << ", " << center->y << ")" << std::endl;
    }
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Square<T>>(center->x, center->y, side);
    }
    bool operator==(const Figure<T>& other) const override {
        if (auto ptr = dynamic_cast<const Square<T>*>(&other)) {
            return center->x == ptr->center->x && center->y == ptr->center->y && side == ptr->side;
        }
        return false;
    }
    explicit operator double() const override { return area(); }
};
