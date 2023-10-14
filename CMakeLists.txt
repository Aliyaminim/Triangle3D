cmake_minimum_required(VERSION 3.25.1)

project(Triangles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -D DEBUG -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)

#add_subdirectory(src)
add_executable(main ./src/main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

#cmake -DCMAKE_BUILD_TYPE=Debug