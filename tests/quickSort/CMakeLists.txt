add_executable(quickSortTest quickSortTest.c)
target_link_libraries(quickSortTest PRIVATE Sorting)

add_test(
    NAME SortIntegers
    COMMAND $<TARGET_FILE:quickSortTest>
)

set_tests_properties(SortIntegers PROPERTIES LABELS "Input not sorted integers - output: sorted integers")