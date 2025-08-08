#pragma once
#include "Point.hpp"
#include <memory>
#include <iostream>

template <class T>
requires Scalar<T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual double area() const = 0;
    virtual void printVertices() const = 0;
    virtual void printCenter() const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual explicit operator double() const = 0;
};
