#include "octo_force.hpp"

int main()
{
    auto indexs = Task::intersect_shapes(Geometry::scan_shapes<double>());
#define PRINT
#ifdef PRINT    
    for (auto index: indexs)
        std::cout << index << ' ';
    std::cout << std::endl;
#endif
    return 0;
}