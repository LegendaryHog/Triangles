#pragma once
#include <algorithm>
#include <cmath>
#include <concepts>

namespace Math
{
template<std::floating_point F>
constexpr F epsilon = 1e-6;
} // namespace Math

namespace Compare
{

template<std::floating_point Float>
inline bool are_equal (Float first, Float second, Float zero_diff = Math::epsilon<Float>, Float rel_diff = Math::epsilon<Float>)
{
    auto diff = std::abs (first - second);

    if (diff < zero_diff)
        return true;
    else
        return (diff < std::max (std::abs (first), std::abs (second)) * rel_diff);
}

} // namespace Compare