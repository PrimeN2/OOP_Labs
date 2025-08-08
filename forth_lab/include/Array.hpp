#pragma once
#include <vector>
#include <stdexcept>

template <class T>
class Array {
private:
    std::vector<T> data;

public:
    Array() = default;

    explicit Array(size_t initial_size) : data(initial_size) {}

    Array(const Array& other) = default;

    Array(Array&& other) noexcept = default;

    Array& operator=(const Array& other) = default;

    Array& operator=(Array&& other) noexcept = default;

    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void push_back(const T& value) {
        data.push_back(value);
    }

    void push_back(T&& value) {
        data.push_back(std::move(value));
    }

    void remove(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index);
    }

    size_t getSize() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};
