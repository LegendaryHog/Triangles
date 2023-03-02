cmake_minimum_required(VERSION 3.8)

project(HW3D
        LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

find_package(GTest REQUIRED)
enable_testing()

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

aux_source_directory(./src SRC)

add_library(triangles_intersection
            STATIC ${SRC})

target_include_directories(triangles_intersection
                           PRIVATE ./include)

add_subdirectory(test)
