# HW3D - triangles

Once upon a time there was a point in 3 dimentions. Then Konstantin Vladimirov came and asked to intersect millions of triangles... To be continued.

# Building
```bash
cmake -B build -DCMAKE_CXX_COMPILETR=[compiler]-DCMAKE_BUILD_TYPE=[Release/Debug]
cmake --build build/
```

# Generating of end to end tests

```bash
cd test/end_to_end
chmod "+x" test_gen.py
./test_gen.py [number of shapes] [characteristic size] [side of cubic space] [name of test] [answer gen=--answer]
```

If last argument (answer gen) equal to --no-answer, than answer will not generated, its will boost generating of tests

# Test correctness of work
```bash
./cmp.py [run file] [name of test]
```

# Comparing brute force and octo tree solutions
```bash
./time_test [path to build directory]
```