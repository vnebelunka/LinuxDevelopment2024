enable_testing()
include(CTest)

add_test(NAME US-100 COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_US.sh 'yes yes yes yes yes yes yes yes' ${CMAKE_BINARY_DIR}/binsearch")
set_property (TEST US-100 PROPERTY PASS_REGULAR_EXPRESSION "answer is 100!")
add_test(NAME RU-100 COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_RU.sh 'да да да да да да да да' ${CMAKE_BINARY_DIR}/binsearch")
set_property (TEST RU-100 PROPERTY PASS_REGULAR_EXPRESSION "ответ это 100!")

add_test(NAME US-50 COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_US.sh 'no yes yes yes yes yes yes yes' ${CMAKE_BINARY_DIR}/binsearch")
set_property (TEST US-50 PROPERTY PASS_REGULAR_EXPRESSION "answer is 50!")
add_test(NAME RU-50 COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_RU.sh 'нет да да да да да да да' ${CMAKE_BINARY_DIR}/binsearch")
set_property (TEST RU-50 PROPERTY PASS_REGULAR_EXPRESSION "ответ это 50!")

add_test(NAME US-46 COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_US.sh 'no yes yes yes no yes yes yes' ${CMAKE_BINARY_DIR}/binsearch")
set_property (TEST US-46 PROPERTY PASS_REGULAR_EXPRESSION "answer is 46!")
add_test(NAME RU-46 COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_RU.sh 'нет да да да нет да да да' ${CMAKE_BINARY_DIR}/binsearch")
set_property (TEST RU-46 PROPERTY PASS_REGULAR_EXPRESSION "ответ это 46!")

add_test(NAME ROM_US-XXXIII COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_US.sh 'no yes no yes no yes no yes' ${CMAKE_BINARY_DIR}/binsearch -r")
set_property (TEST ROM_US-XXXIII PROPERTY PASS_REGULAR_EXPRESSION "answer is XXXIII!")
add_test(NAME ROM_RU-XXXIII COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_RU.sh 'нет да нет да нет да нет да' ${CMAKE_BINARY_DIR}/binsearch -r")
set_property (TEST ROM_RU-XXXIII PROPERTY PASS_REGULAR_EXPRESSION "ответ это XXXIII!")

add_test(NAME ROM_US-I COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_US.sh 'no no no no no no no no' ${CMAKE_BINARY_DIR}/binsearch -r")
set_property (TEST ROM_US-I PROPERTY PASS_REGULAR_EXPRESSION "answer is I!")
add_test(NAME ROM_RU-I COMMAND bash -c "${CMAKE_CURRENT_SOURCE_DIR}/test_RU.sh 'нет нет нет нет нет нет нет нет' ${CMAKE_BINARY_DIR}/binsearch -r")
set_property (TEST ROM_RU-I PROPERTY PASS_REGULAR_EXPRESSION "ответ это I!")