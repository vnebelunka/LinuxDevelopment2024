cmake_minimum_required(VERSION 3.20)
project(I18N)

find_package(Gettext REQUIRED)
if(Gettext_FOUND)
  message(STATUS "Gettext found:")
  message(STATUS " Version: ${GETTEXT_VERSION_STRING}")
else()
  message(STATUS "Gettext Not found!")
endif()

add_executable(binsearch binsearch.c)
target_compile_definitions(
  binsearch PRIVATE TEXTDOMAINDIR="${CMAKE_CURRENT_BINARY_DIR}/locale")
set(TEXTDOMAIN "messages")

file(GLOB ffs "lang/*.po")
foreach(ff IN LISTS ffs)
  get_filename_component(LANG ${ff} NAME_WE)
  message(${LANG})
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale/${LANG})
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale/${LANG}/LC_MESSAGES)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/locale/${LANG}/LC_MESSAGES/${TEXTDOMAIN}.mo
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lang/${LANG}.po
    COMMAND
      msgfmt -o
      ${CMAKE_CURRENT_BINARY_DIR}/locale/${LANG}/LC_MESSAGES/${TEXTDOMAIN}.mo
      ${CMAKE_CURRENT_SOURCE_DIR}/lang/${LANG}.po)

  add_custom_target(
    gen_${LANG} ALL
    DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/locale/${LANG}/LC_MESSAGES/${TEXTDOMAIN}.mo)
endforeach()
