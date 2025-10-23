#include "Eleven.hpp"
#include <iostream>

int main(void) {
    Eleven a("1A23");
    Eleven b("45");
    Eleven result = a.add(b);

    std::cout << result.toString() << std::endl;
}