cmake_minimum_required(VERSION 3.25.1)

project(Triangles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)

#add_subdirectory(src)
add_executable(main ./src/main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

#add_executable(prim ./include/primitives.cpp)