configure_file(config.h.in config.h)
include_directories(${PROJECT_BINARY_BIN})

add_executable(min-mt-lcm main.c)
