#include "task.hpp"

int main()
{
    auto shapes = Task::scan_shapes<double>();
    Task::intersect_shapes(shapes);
    return 0;
}