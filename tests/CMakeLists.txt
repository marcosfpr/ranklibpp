include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
  test_ltrpp
  main.cpp
  unit/learning/DataPointTest.cpp
  unit/learning/RankListTest.cpp
  unit/learning/RankerTest.cpp
  unit/metric/MAPScorerTest.cpp
  unit/utils/KeyValueTest.cpp
)

target_link_libraries(test_ltrpp ltr pthread gtest gtest_main)

# Create testing target and redirect its output to `Testing` folder
add_test(NAME test_ltrpp COMMAND test_ltrpp WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(test_ltrpp PROPERTIES TIMEOUT 30) 

include(FindValgrind)

add_custom_target(valgrind_test_ltrpp
  COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:test_ltrpp>
  DEPENDS test_ltrpp
)