#include "brute_force.hpp"

int main()
{
    auto indexs = Task::intersect_shapes(Geometry::scan_shapes<double>());
    for (auto index: indexs)
        std::cout << index << ' ';
    std::cout << std::endl;
    return 0;
}