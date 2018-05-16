cmake_minimum_required(VERSION 3.9)
project(te
  LANGUAGES CXX
  VERSION 0.0.1
  )

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Werror -pedantic-errors")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(CUTE_DIRECTORY "${PROJECT_SOURCE_DIR}/cute")

if(EXISTS "${CUTE_DIRECTORY}/cute/cute.h")
  message(STATUS "The CUTE headers were found. Enabling unit tests. Override by setting 'ENABLE_TESTS' to OFF")
  set(CUTE_FOUND YES)
else()
  message(STATUS "The CUTE headers were not found. Disabling unit tests")
  set(CUTE_FOUND NO)
endif()

option(ENABLE_TESTS "Enable unit tests" ${CUTE_FOUND})

find_package(Threads)

include_directories(include)

#add_subdirectory(source)
add_subdirectory(include)
#add_subdirectory(demo)

if(${ENABLE_TESTS})
  enable_testing()
  include_directories("${CUTE_DIRECTORY}")
  add_subdirectory("tests")
endif()

