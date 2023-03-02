#pragma once
#include <algorithm>
#include <cmath>

namespace cmp
{

constexpr double epsilon = 1e-6;

inline bool are_equal (const double first, const double second, const double zero_diff = epsilon,
                       const double rel_diff = epsilon)
{
    auto diff = std::abs (first - second);

    if (diff < zero_diff)
        return true;
    else
        return (diff < std::max (std::abs (first), std::abs (second)) * rel_diff);
}

} // namespace cmp