cmake_minimum_required(VERSION 3.1...3.26)
project(minimal-multithreaded-lcm
  VERSION 0.0.1
  DESCRIPTION "A minimal example using LCM and multiple threads"
  HOMEPAGE_URL "https://github.com/bluesquall/minimal-multithreaded-lcm"
  LANGUAGES C)

configure_file(src/config.h.in src/config.h)
include_directories(${PROJECT_BINARY_BIN})

add_executable(min-mt-lcm src/main.c)
