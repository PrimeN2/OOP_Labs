#include <iostream>
#include "closest_pair_tonum.hpp"

int main() {
    Pair pair = closest_pair_tonum(50);
    std::cout << pair.upper << ", "<< pair.lower << std::endl;

    return 0;
}