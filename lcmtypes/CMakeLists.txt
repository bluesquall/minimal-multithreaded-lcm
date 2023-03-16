include(GenerateExportHeader)

if(JAVA_FOUND)
  set(java_args JAVA_SOURCES java_sources)
endif()
if(PYTHONINTERP_FOUND)
  set(python_args PYTHON_SOURCES python_install_sources)
endif()

lcm_wrap_types(
  C_EXPORT min_mt_lcmtypes
  C_SOURCES c_sources
  C_HEADERS c_install_headers
  ${python_args}
  ${java_args}
  minmt_example_t.lcm
  minmt_colors_t.lcm
)

lcm_add_library(min_mt_lcmtypes C ${c_sources} ${c_install_headers})
generate_export_header(min_mt_lcmtypes)
target_include_directories(min_mt_lcmtypes
  INTERFACE  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)


if(JAVA_FOUND)
  add_jar(min_mt_lcmtypes-jar
    OUTPUT_NAME min_mt_lcmtypes
    INCLUDE_JARS lcm-java
    SOURCES ${java_sources}
  )
endif()

lcm_install_headers(DESTINATION include
  ${CMAKE_CURRENT_BINARY_DIR}/my_lcmtypes_export.h
  ${c_install_headers}
  ${cpp_install_headers}
)

install(TARGETS min_mt_lcmtypes
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  ARCHIVE DESTINATION lib${LIB_SUFFIX}
  INCLUDES DESTINATION include
)

if(JAVA_FOUND)
  install_jar(min_mt_lcmtypes-jar share/java)
endif()
if(PYTHONINTERP_FOUND)
  lcm_install_python(${python_install_sources})
endif()
