add_executable("te_tests"      te_tests.cpp)
add_executable("te_tests_m001" te_tests_m001.cpp)
add_executable("te_tests_m002" te_tests_m002.cpp)
add_executable("te_tests_m003" te_tests_m003.cpp)
add_executable("te_tests_m004" te_tests_m004.cpp)
add_executable("te_tests_m005" te_tests_m005.cpp)
add_executable("te_tests_m006" te_tests_m006.cpp)
add_executable("te_tests_m007" te_tests_m007.cpp)
add_executable("te_tests_m008" te_tests_m008.cpp)
add_executable("te_tests_m009" te_tests_m009.cpp)
add_executable("te_tests_m010" te_tests_m010.cpp)
add_executable("te_tests_m011" te_tests_m011.cpp)
add_executable("te_tests_m012" te_tests_m012.cpp)

add_test(NAME "te_tests"      COMMAND te_tests)
add_test(NAME "te_tests_m001" COMMAND te_tests_m001)
add_test(NAME "te_tests_m002" COMMAND te_tests_m002)
add_test(NAME "te_tests_m003" COMMAND te_tests_m003)
add_test(NAME "te_tests_m004" COMMAND te_tests_m004)
add_test(NAME "te_tests_m005" COMMAND te_tests_m005)
add_test(NAME "te_tests_m006" COMMAND te_tests_m006)
add_test(NAME "te_tests_m007" COMMAND te_tests_m007)
add_test(NAME "te_tests_m008" COMMAND te_tests_m008)
add_test(NAME "te_tests_m009" COMMAND te_tests_m009)
add_test(NAME "te_tests_m010" COMMAND te_tests_m010)
add_test(NAME "te_tests_m011" COMMAND te_tests_m011)
add_test(NAME "te_tests_m012" COMMAND te_tests_m012)

add_custom_target("run_te_test"
  ALL
  DEPENDS "te_tests" "te_tests_m001" "te_tests_m002" "te_tests_m003" "te_tests_m004" "te_tests_m005" "te_tests_m006" "te_tests_m007" "te_tests_m008" "te_tests_m009" "te_tests_m010" "te_tests_m011" "te_tests_m012"
  COMMAND ${CMAKE_COMMAND} "--build" "${CMAKE_BINARY_DIR}" "--target" "test"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Executing 'te' unit tests"
  )
