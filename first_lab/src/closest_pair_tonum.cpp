#include <iostream>
#include <cmath>
#include "closest_pair_tonum.hpp"

Pair closest_pair_tonum(int upper_limit) {
    int upper = -1, lower = -1;

    for (int i = upper_limit - 1; i > 1; --i) {
        for (int j = i - 1; j > 0; --j) {
            int sqrt_sum = static_cast<int>(sqrt(i+j));
            int sqrt_dif = static_cast<int>(sqrt(i-j));
            
            if (sqrt_sum * sqrt_sum == (i+j) && sqrt_dif * sqrt_dif == (i - j)) {
                upper = i;
                lower = j;
                
                break;
            }
        }

        if (upper != -1) 
            break;
    }

    return {upper, lower};
}