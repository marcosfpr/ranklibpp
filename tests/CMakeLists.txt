include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
  test_ranklib
  main.cpp
  unit/DataPointTest.cpp
  unit/RankListTest.cpp
  unit/MAPScorerTest.cpp
)

target_link_libraries(test_ranklib ranklib pthread gtest gtest_main)

# Create testing target and redirect its output to `Testing` folder
add_test(NAME test_ranklib COMMAND test_ranklib WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(test_ranklib PROPERTIES TIMEOUT 30) 

include(FindValgrind)

add_custom_target(valgrind_test_ranklib
  COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:test_ranklib>
  DEPENDS test_ranklib
)