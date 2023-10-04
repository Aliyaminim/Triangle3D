project(Google_tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../)

add_executable(test1 ../header.hpp test1.cpp)
target_link_libraries(test1 gtest gtest_main)

