cmake_minimum_required(VERSION 3.20)
project(RHASH_PROJECT)

enable_testing()

option(FORCE_GETLINE "don't used readline even it is found" OFF)

add_executable(rhasher rhasher.c)

find_library(RHASH rhash REQUIRED)
message("rhash library found")
target_link_libraries(rhasher rhash)

find_library(READLINE readline)
if(READLINE)
    message("readline library founded")
    if(NOT FORCE_GETLINE)
        target_link_libraries(rhasher readline)
        target_compile_definitions(rhasher PRIVATE USE_READLINE)
    endif()
else()
    message(WARNING "readline not found and won't be used")
endif()


find_program (BASH_PROGRAM bash)

add_test(TEST_SHA1 ${BASH_PROGRAM} ${PROJECT_SOURCE_DIR}/test/testsha1.sh ${PROJECT_BINARY_DIR}/rhasher)
add_test(TEST_MD51 ${BASH_PROGRAM} ${PROJECT_SOURCE_DIR}/test/testmd5.sh ${PROJECT_BINARY_DIR}/rhasher)