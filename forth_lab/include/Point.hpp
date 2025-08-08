#pragma once
#include <concepts>
#include <cmath>

template <class T>
concept Scalar = std::is_arithmetic_v<T>;

template <class T>
requires Scalar<T>
struct Point {
    T x;
    T y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
};
