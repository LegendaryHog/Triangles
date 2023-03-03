#pragma once
#include <algorithm>
#include <cmath>
#include <concepts>

namespace Compare
{

template<std::floating_point Float>
inline bool are_equal (Float first, Float second, Float zero_diff = 1e-6, Float rel_diff = 1e-6)
{
    auto diff = std::abs (first - second);

    if (diff < zero_diff)
        return true;
    else
        return (diff < std::max (std::abs (first), std::abs (second)) * rel_diff);
}

} // namespace cmp