cmake_minimum_required(VERSION 3.0.0)
project(Chapter4 VERSION 0.1.0 LANGUAGES C)

add_library(Heap STATIC heap.c heap.h)
add_library(Sorting STATIC sorting.c sorting.h)
add_library(Exercises STATIC exercises.c exercises.h)
add_library(LeetCode STATIC leetCode.c leetCode.h)

add_executable(Chapter4 main.c)

target_link_libraries(Exercises PRIVATE Sorting)
target_link_libraries(Exercises PRIVATE Heap)
target_link_libraries(Chapter4 PRIVATE Heap)
target_link_libraries(Chapter4 PRIVATE Sorting)
target_link_libraries(Chapter4 PRIVATE Exercises)
target_link_libraries(Chapter4 PRIVATE LeetCode)

include(CTest)
enable_testing()

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
