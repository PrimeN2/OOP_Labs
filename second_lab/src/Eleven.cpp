#include "Eleven.hpp"
#include <algorithm>
#include <sstream>
#include <cstring>

Eleven::Eleven()
    : digits_(new unsigned char[1]{0}), size_(1) {}

Eleven::Eleven(const size_t& n, unsigned char t)
    : size_(n) {
    if (n == 0) {
        size_ = 1;
    }
    digits_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; ++i) {
        if (!isValidDigit(t)) {
            delete[] digits_;
            throw std::invalid_argument("Цифра должна быть в диапазоне [0, 10]");
        }
        digits_[i] = t;
    }
    normalize();
}

Eleven::Eleven(const std::initializer_list<unsigned char>& t)
    : size_(t.size()) {
    if (size_ == 0) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }
    digits_ = new unsigned char[size_];
    size_t i = 0;
    for (auto digit : t) {
        if (!isValidDigit(digit)) {
            delete[] digits_;
            throw std::invalid_argument("Цифра должна быть в диапазоне [0, 10]");
        }
        digits_[i++] = digit;
    }
    normalize();
}

Eleven::Eleven(const std::string& t)
    : size_(t.length()), digits_(nullptr) {
    if (size_ == 0) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }

    digits_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; ++i) {
        char c = t[i];
        unsigned char digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c == 'A' || c == 'a') {
            digit = 10;
        } else {
            delete[] digits_;
            throw std::invalid_argument("Недопустимый символ в строке: " + std::string(1, c));
        }
        if (!isValidDigit(digit)) {
            delete[] digits_;
            throw std::invalid_argument("Цифра должна быть в диапазоне [0, 10]");
        }
        digits_[size_ - 1 - i] = digit;
    }
    normalize();
}

Eleven::Eleven(const Eleven& other)
    : size_(other.size_) {
    digits_ = new unsigned char[size_];
    std::memcpy(digits_, other.digits_, size_ * sizeof(unsigned char));
}

Eleven::Eleven(Eleven&& other) noexcept
    : digits_(other.digits_), size_(other.size_) {
    other.digits_ = nullptr;
    other.size_ = 0;
}

Eleven::~Eleven() noexcept {
    delete[] digits_;
}

Eleven Eleven::add(const Eleven& other) const {
    size_t max_size = std::max(size_, other.size_);
    size_t result_size = max_size + 1;
    unsigned char* result_digits = new unsigned char[result_size]{0};

    unsigned char carry = 0;
    for (size_t i = 0; i < result_size; ++i) {
        unsigned char d1 = (i < size_) ? digits_[i] : 0;
        unsigned char d2 = (i < other.size_) ? other.digits_[i] : 0;
        unsigned char sum = d1 + d2 + carry;
        carry = sum / 11;
        result_digits[i] = sum % 11;
    }

    Eleven result;
    delete[] result.digits_;
    result.digits_ = result_digits;
    result.size_ = result_size;
    result.normalize();
    return result;
}

Eleven Eleven::subtract(const Eleven& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Результат вычитания будет отрицательным");
    }

    size_t max_size = std::max(size_, other.size_);
    unsigned char* result_digits = new unsigned char[max_size]{0};

    int borrow = 0;
    for (size_t i = 0; i < max_size; ++i) {
        int d1 = (i < size_) ? static_cast<int>(digits_[i]) : 0;
        int d2 = (i < other.size_) ? static_cast<int>(other.digits_[i]) : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result_digits[i] = static_cast<unsigned char>(diff);
    }

    Eleven result;
    delete[] result.digits_;
    result.digits_ = result_digits;
    result.size_ = max_size;
    result.normalize();
    return result;
}

Eleven Eleven::copy() const {
    return Eleven(*this);
}

bool Eleven::greaterThan(const Eleven& other) const {
    if (size_ != other.size_) {
        return size_ > other.size_;
    }
    for (int i = size_ - 1; i >= 0; --i) {
        if (digits_[i] != other.digits_[i]) {
            return digits_[i] > other.digits_[i];
        }
    }
    return false;
}

bool Eleven::lessThan(const Eleven& other) const {
    if (size_ != other.size_) {
        return size_ < other.size_;
    }
    for (int i = size_ - 1; i >= 0; --i) {
        if (digits_[i] != other.digits_[i]) {
            return digits_[i] < other.digits_[i];
        }
    }
    return false;
}

bool Eleven::equalTo(const Eleven& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (digits_[i] != other.digits_[i]) {
            return false;
        }
    }
    return true;
}

std::string Eleven::toString() const {
    if (size_ == 0) {
        return "0";
    }
    std::ostringstream oss;
    for (int i = size_ - 1; i >= 0; --i) {
        if (digits_[i] < 10) {
            oss << static_cast<char>('0' + digits_[i]);
        } else {
            oss << 'A';
        }
    }
    return oss.str();
}

size_t Eleven::getSize() const {
    return size_;
}

void Eleven::normalize() {
    if (size_ == 0) return;

    size_t i = size_ - 1;
    while (i > 0 && digits_[i] == 0) {
        --i;
    }

    if (i == 0 && digits_[0] == 0) {
        delete[] digits_;
        digits_ = new unsigned char[1]{0};
        size_ = 1;
        return;
    }

    if (i != size_ - 1) {
        size_t new_size = i + 1;
        unsigned char* new_digits = new unsigned char[new_size];
        std::memcpy(new_digits, digits_, new_size * sizeof(unsigned char));
        delete[] digits_;
        digits_ = new_digits;
        size_ = new_size;
    }
}

bool Eleven::isValidDigit(unsigned char d) {
    return d <= 10;
}