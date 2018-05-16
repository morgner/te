add_executable("te_tests"      te_tests.cpp)
add_executable("te_tests_m001" te_tests_m001.cpp)
add_executable("te_tests_m002" te_tests_m002.cpp)
add_executable("te_tests_m003" te_tests_m003.cpp)
add_executable("te_tests_m004" te_tests_m004.cpp)

add_test(NAME "te_tests"      COMMAND te_tests)
add_test(NAME "te_tests_m001" COMMAND te_tests_m001)
add_test(NAME "te_tests_m002" COMMAND te_tests_m002)
add_test(NAME "te_tests_m003" COMMAND te_tests_m003)
add_test(NAME "te_tests_m004" COMMAND te_tests_m004)

add_custom_target("run_te_test"
  ALL
  DEPENDS "te_tests" "te_tests_m001" "te_tests_m002" "te_tests_m003" "te_tests_m004"
  COMMAND ${CMAKE_COMMAND} "--build" "${CMAKE_BINARY_DIR}" "--target" "test"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Executing 'te' unit tests"
  )
