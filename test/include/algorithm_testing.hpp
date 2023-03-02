#ifndef TEST_INCLUDE_ALGORITHM_TESTING_HPP
#define TEST_INCLUDE_ALGORITHM_TESTING_HPP

#include "triangle.hpp"
#include "segment.hpp"

namespace Geometry
{

enum Loc_Points {
    In_Same = 1,
    In_Different = -1,
    On_Line = 0,
};

Loc_Points laying_in_same_half(const Point& A, const Point& B, const Point& C, const Point& D);
bool point_belong_triangle(const Point& point_A, const Triangle& tr);
bool are_intersecting(const Segment& seg1, const Segment& seg2);
bool seg_tr_intersecting_2D(const Segment& seg, const Triangle& tr);
bool seg_tr_intersecting_3D(const Segment& seg, const Triangle& tr);
bool segment_and_triangle_intersecting(const Segment& seg, const Triangle& tr);
bool intersection_in_2D (const Triangle &tr_1_, const Triangle &tr_2_);
inline Loc_2D magic_product (const Point &P, const Point &Q, const Point &M);
void space_transformation (Triangle &tr_1, Triangle &tr_2);
void transform_triangle (Triangle &tr_1, const Loc_3D P1_loc, const Loc_3D Q1_loc,
                         const Loc_3D R1_loc, Triangle &tr_2);

enum class Case {          //3^1   //3^0
    Point_n_Point       = 0 * 3 + 0 * 1,
    Point_n_Segment     = 0 * 3 + 1 * 1,
    Point_n_Triangle    = 0 * 3 + 2 * 1,
    Segment_n_Point     = 1 * 3 + 0 * 1,
    Segment_n_Segment   = 1 * 3 + 1 * 1,
    Segment_n_Triangle  = 1 * 3 + 2 * 1,
    Triangle_n_Point    = 2 * 3 + 0 * 1,
    Triangle_n_Segment  = 2 * 3 + 1 * 1,
    Triangle_n_Triangle = 2 * 3 + 2 * 1,
};

Case case_of_intersection(const Triangle& tr1, const Triangle& tr2);
}

#endif // TEST_INCLUDE_ALGORITHM_TESTING_HPP
