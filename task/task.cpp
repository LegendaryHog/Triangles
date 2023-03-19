#define OCTO_FORCE

#ifdef  BRUTE_FORCE
    #include "brute_force.hpp"
#endif

#ifdef OCTO_FORCE
    #include "octo_force.hpp"
#endif

int main()
{
    auto indexs = Task::intersect_shapes(Geometry::scan_shapes<double>());
    for (auto index: indexs)
        std::cout << index << ' ';
    std::cout << std::endl;
    return 0;
}