cmake_minimum_required(VERSION 3.25.1)

project(Triangles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)

add_executable(main main.cpp)