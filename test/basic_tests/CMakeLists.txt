aux_source_directory(./src SRC_LIST)

add_executable(basic_tests ${SRC_LIST})

target_link_libraries(basic_tests
                      PRIVATE ${GTEST_LIBRARIES} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(basic_tests)
