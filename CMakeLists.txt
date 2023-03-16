cmake_minimum_required(VERSION 3.1...3.26)
project(minimal-multithreaded-lcm
  VERSION 0.0.1
  DESCRIPTION "A minimal example using LCM and multiple threads"
  HOMEPAGE_URL "https://github.com/bluesquall/minimal-multithreaded-lcm"
  LANGUAGES C)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(lcm REQUIRED)
include(${LCM_USE_FILE})

find_package(PythonInterp)
find_package(Java)

if(JAVA_FOUND)
  include(UseJava)
endif()

add_subdirectory(lcmtypes)
add_subdirectory(src)
