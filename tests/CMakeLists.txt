add_library(te_test_driver OBJECT "te_test_driver.cpp")

macro(cute_suite SUITE)
  set(TEST_TARGET "te_test_${SUITE}")
  set(SUITE_FILE "suites/${SUITE}.cpp")
  add_executable("${TEST_TARGET}" $<TARGET_OBJECTS:te_test_driver> ${SUITE_FILE})
  target_link_libraries("${TEST_TARGET}" stdc++fs)
  target_include_directories("${TEST_TARGET}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  set_target_properties("${TEST_TARGET}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test_suites")
  add_test(NAME "${SUITE}" COMMAND "${TEST_TARGET}")
  list(APPEND TE_TEST_TARGETS "${TEST_TARGET}")
endmacro()

cute_suite("simple_variable_replacement")
cute_suite("invalid_template_syntax")
cute_suite("control_flow_constructs")

message(STATUS "Registered Suites: ${TE_TEST_TARGETS}")

add_custom_target("te_tests"
  ALL
  DEPENDS ${TE_TEST_TARGETS}
  COMMAND "ctest"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Executing 'te' unit tests"
  )
