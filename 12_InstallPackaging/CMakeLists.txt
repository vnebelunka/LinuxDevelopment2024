cmake_minimum_required(VERSION 3.20)
project(documentation)

option(BUILD_DOCS "build documentation with doxygen" ON)

if(BUILD_DOCS)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_USE_MATHJAX YES) # need for TEX formulas in documentation
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_MAN_EXTENSION .1)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    doxygen_add_docs(docs ALL ${PROJECT_SOURCE_DIR})
  else()
    message(
      WARNING "No doxygen package found. Documentation won't be generated")
  endif()
endif()

find_package(Gettext REQUIRED)
if(Gettext_FOUND)
  message(STATUS "Gettext found:")
  message(STATUS " Version: ${GETTEXT_VERSION_STRING}")
else()
  message(STATUS "Gettext Not found!")
endif()

add_library(binsearchlib STATIC src/binsearch.c)
set_target_properties(binsearchlib PROPERTIES PUBLIC_HEADER include/binsearch.h)
target_include_directories(binsearchlib PUBLIC include)

add_executable(binsearch main.c)
target_link_libraries(binsearch PRIVATE binsearchlib)

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

include(GNUInstallDirs)

include(install.cmake)

enable_testing()
include(CTest)
add_subdirectory(test)