#pragma once

struct Pair
{
    int upper;
    int lower;

    bool operator==(const Pair& other) const {
        return upper == other.upper && lower == other.lower;
    }
};

Pair closest_pair_tonum(int upper_limit);