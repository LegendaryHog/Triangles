aux_source_directory(./src SRC_LIST)

add_executable(octo_tree_tests ${SRC_LIST})

target_link_libraries(octo_tree_tests
                      PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(octo_tree_tests)