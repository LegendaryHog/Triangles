#pragma once
#include "triangle.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace Geometry
{

template<std::floating_point Float>
bool are_intersecting (const Triangle<Float>& tr_1, const Triangle<Float>& tr_2);

} // namespace Geometry