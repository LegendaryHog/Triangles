#include "octo_force.hpp"

int main()
{
    auto indexs = Task::intersect_shapes(Geometry::scan_shapes<double>());
#if 0    
    for (auto index: indexs)
        std::cout << index << ' ';
    std::cout << std::endl;
#endif
    return 0;
}