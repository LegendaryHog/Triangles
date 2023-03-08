aux_source_directory(./src SRC_LIST)

add_executable(task_test ${SRC_LIST})

target_link_libraries(task_test
                      PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(task_test)