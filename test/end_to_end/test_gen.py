#! /usr/bin/env python3
import Geometry3D as geom
import random as rand
import math
import sys
from typing import List

# number of shapes    - 1 arg
# max "size" of shape - 2 arr
# size of space(cube) - 3 arg
# name of file        - 4 arg
# flag for time test  - 5 arg

num_of_shapes = int(sys.argv[1])
max_size      = float(sys.argv[2])
size_of_space = float(sys.argv[3])
name_of_file  = sys.argv[4]
no_answ = False
if len(sys.argv) == 6 and sys.argv[5] == '--no-answer':
    no_answ = True


def make_base_for_point():
    return geom.Point(rand.uniform(0.0, size_of_space), rand.uniform(0.0, size_of_space), 0)#rand.uniform(0.0, size_of_space))
    
def generate_point(list_of_points):
    p1 = geom.Point(rand.uniform(0.0, size_of_space), rand.uniform(0.0, size_of_space), 0)#rand.uniform(0.0, size_of_space))
    list_of_points.append(p1)
    list_of_points.append(p1)
    list_of_points.append(p1)
    return p1

def make_point(point: geom.Point):
    return geom.Point(rand.uniform(max(point.x - max_size, 0.0), min(point.x + max_size, size_of_space)),
                      rand.uniform(max(point.y - max_size, 0.0), min(point.y + max_size, size_of_space)),
                      0)
                      #rand.uniform(max(point.z - max_size, 0.0), min(point.z + max_size, size_of_space)))
                      
def is_triangle(tr: geom.ConvexPolygon):
    return not math.isclose(tr.area(), 0.0)

def generate_triangle(list_of_points):
    is_tr = False
    base = make_base_for_point()
    while is_tr == False:
        p1 = make_point(base)
        p2 = make_point(base)
        p3 = make_point(base)
        tr = geom.ConvexPolygon((p1, p2, p3))
        is_tr = is_triangle(tr)
    list_of_points.append(p1)
    list_of_points.append(p2)
    list_of_points.append(p3)
    return tr

def is_segment(seg: geom.Segment):
    return not math.isclose(seg.length(), 0.0)

def generate_segment(list_of_points): 
    is_seg = False
    base = make_base_for_point()
    while is_seg == False:
        p1 = make_point(base)
        p2 = make_point(base)
        seg = geom.Segment(p1, p2)
        is_seg = is_segment(seg)
    list_of_points.append(p1)
    list_of_points.append(p2)
    list_of_points.append(geom.Point((geom.Vector(p1) + geom.Vector(p2))*0.5))
    return seg

def generate_shapes():
    list_of_shapes = []
    list_of_points = []
    for _ in range(num_of_shapes):
        shape_type = rand.randint(0, 10)
        if shape_type in range(0,7):
            list_of_shapes.append(generate_triangle(list_of_points))
        elif shape_type in range(8, 9):
            list_of_shapes.append(generate_segment(list_of_points))
        else:
            list_of_shapes.append(generate_point(list_of_points))
    return list_of_shapes, list_of_points

def intersect_shapes(list_of_shapes):
    len_of_list = len(list_of_shapes)
    set_of_ins_ind = set()
    for i in range(len_of_list - 1):
        for j in range(i + 1, len_of_list):    
            if type(geom.intersection(list_of_shapes[i], list_of_shapes[j])) != type(None):
                set_of_ins_ind.add(i)
                set_of_ins_ind.add(j)
    return set_of_ins_ind

def print_list_of_points(list_of_points: List[geom.Point]):
    file = open(name_of_file + "_task", 'w')
    file.write(str(num_of_shapes) + '\n')
    j = 0
    for i in list_of_points:
        if j % 3 == 0:
            file.write('\n')
        j+=1
        file.write(str(i.x) + ' ' + str(i.y) + ' ' +  str(i.z) + '\n')
    file.write('\n')

def print_list_of_ins_ind(set_of_ins_ind):
    file = open(name_of_file + "_answ", 'w')
    for i in set_of_ins_ind:
        file.write(str(i) + ' ')
    file.write('\n')

def main():
    list_of_shapes, list_of_points = generate_shapes()
    print_list_of_points(list_of_points)

    if no_answ == False:
        set_of_ins_ind = intersect_shapes(list_of_shapes)
        print_list_of_ins_ind(set_of_ins_ind)

main()