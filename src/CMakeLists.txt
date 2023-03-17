
add_executable(min-mt-lcm main.c)
target_include_directories(min-mt-lcm PRIVATE ${MIN_MT_LCMTYPES_INCLUDE_DIRS})
target_link_libraries(min-mt-lcm min_mt_lcmtypes)
