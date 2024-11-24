cmake_minimum_required(VERSION 3.20)
project(libtesting)

add_library(buf SHARED buf.c)
target_compile_options(buf PUBLIC -std=c99 -Wall -Wextra -g3)
target_compile_options(buf PUBLIC -fprofile-arcs -ftest-coverage)
target_link_options(buf PUBLIC -coverage)

set(TESTS "capacity init" 
       "size init" 
       "size 1" 
       "value" 
       "clear" 
       "clear not-free" 
       "free" 
       "clear empty" 
       "clear no-op" 
       "size 10000" 
       "match 10000" 
       "grow 1000"
       "size 0 (grow)"
       "trunc 100"
       "size 4"
       "pop 3"
       "size 3"
       "pop 2"
       "pop 1"
       "pop 0"
       "size 0 (pop)"
       )

include(CTest)
enable_testing()

add_executable(test_buf tests.c)
target_link_libraries(test_buf PUBLIC buf)
target_compile_options(test_buf PRIVATE -std=c99 -Wall -Wextra -g3)


foreach(TEST_NAME IN LISTS TESTS)
    add_test(NAME ${TEST_NAME} COMMAND test_buf ${TEST_NAME})
endforeach()

add_test(NAME benchmark COMMAND test_buf "benchmark" 558d2750ae0e0887)