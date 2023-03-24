# Triagles intersection

Our project with Dany aka "BileyHarryCopter" Gerasimenko (https://github.com/BileyHarryCopter). We solved HW3D problem of Konstantin Vladimirov:
```
Input 0 < N < 1'000'000, after this N set of points in 3D which is vertex of triangles.
Output: indexs of all triangles which has collision with other.
```

For this project we wrote and tested geometric primitives: Vector, Point, Segment, Triangle, Line, Plane. Also we wrote intersection algorithm for Point, Segment and Triangle.

At first we wrote brute force intersection of all shapes, but it is too long. Now we wrote spatial partitioning algorithm which use Octo Tree.
## Building
```bash
cmake -B build -DCMAKE_CXX_COMPILETR=[compiler]-DCMAKE_BUILD_TYPE=[Release/Debug]
cmake --build build/
```

## How to run brute force solution?
```bash
./build/task/brute_force/brute_force
```

## How to run Octo Tree solution?
```bash
./build/task/brute_force/brute_force
```

## Generating of end to end tests

```bash
cd test/end_to_end
chmod "+x" test_gen.py
./test_gen.py [number of shapes] [characteristic size] [side of cubic space] [name of test] [answer gen=--answer]
```

If last argument (answer gen) equal to --no-answer, than answer will not generated, its will boost generating of tests

## Test correctness of work
```bash
./cmp.py [run file] [name of test]
```

## Comparing brute force and octo tree solutions
```bash
./time_test [path to build directory]
```