aux_source_directory(./src SRC_LIST)

add_executable(algorithm_tests ${SRC_LIST})

target_link_libraries(algorithm_tests
                      PRIVATE triangles_intersection
                      PRIVATE ${GTEST_LIBRARIES})

target_include_directories(algorithm_tests
                           PRIVATE ../include
                           PRIVATE ../../include)

gtest_discover_tests(algorithm_tests)
