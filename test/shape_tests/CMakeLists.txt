aux_source_directory(./src SRC_LIST)

add_executable(shape_test ${SRC_LIST})

target_link_libraries(shape_test
                      PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(shape_test)