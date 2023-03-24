# <div align="center">Triagles intersection </div>

Our project with Dany aka [BileyHarryCopter](https://github.com/BileyHarryCopter). We solved HW3D problem on course "Uses and applications of C++ language" by [K.I.Vladimirov](https://github.com/tilir):
```
Input:  0 < N < 1'000'000, after this N set of points in 3D which is vertex of triangles.
Output: Indexs of all intersectred triangles.
```

For this project we wrote and tested geometric primitives: Vector, Point, Segment, Triangle, Line, Plane. Also we implemented intersection algorithm for Point, Segment and Triangle from the [arcitcle](/article/RR-4488.pdf). \
(We also detect a little problem in the article in case **5a** of decision tree when p1 belongs to region R2 (*page 17, Figure 10*): there is should be checked condition of [p2,q1,r1], instead of [r2,p2,r1])

At the first we wrote brute force intersection of all shapes, but it is too long. Now we wrote spatial partitioning algorithm which uses Octree.

## Requirements

CMake with version 3.8 (or higher)

Python3 with version 3.10.6 (or higher)

Installed library of Geometry3D by command under(for generation random [tests](#generating-of-end-to-end-tests)):
```
pip install Geometry3D
```

## How to clone and build
```
git clone git@github.com:LegendaryHog/Triangles.git
```

```bash
cmake -B build -DCMAKE_CXX_COMPILER=[compiler]-DCMAKE_BUILD_TYPE=[Release/Debug]
cmake --build build/
```

## How to run brute force solution
```bash
./build/task/brute_force/brute_force
```

## How to run Octree solution
```bash
./build/task/brute_force/brute_force
```

## Generating of end-to-end tests

```bash
cd test/end_to_end
chmod "+x" test_gen.py
./test_gen.py [number of shapes] [characteristic size] [side of cubic space] [name of test] [answer gen=--answer]
```

If the last argument (answer gen) equals to --no-answer, than answer will not generated, it will boost generating of tests

## Test correctness of work
```bash
./cmp.py [run file] [name of test]
```

## Comparing brute force and octree solutions
```bash
./time_test -c [path to build directory] [name of file with task] 
```