cmake_minimum_required(VERSION 3.19)
project(LongMath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(LongNumber)
add_subdirectory(LongNumber)

add_executable(main main.cpp)
target_link_libraries(main LongNumber)

add_executable(pi pi.cpp)
target_link_libraries(pi LongNumber)

add_executable(test test.cpp)
target_link_libraries(test LongNumber)