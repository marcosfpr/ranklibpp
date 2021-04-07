# set env variables
set(OHSUMED "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/OHSUMED")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
  test_ltrpp
  main.cpp
  unit/learning/DataPointTest.cpp
  unit/learning/RankListTest.cpp
  unit/learning/DataSetTest.cpp
  unit/learning/RankerTest.cpp
  unit/metric/MAPScorerTest.cpp
  unit/metric/PrecisionScorerTest.cpp
  unit/utils/KeyValueTest.cpp

  unit/learning/ensemble/AdaRankTest.cpp
)

add_executable(
        func_ltrpp
        functional/RankingAdaRank.cpp
)

target_link_libraries(test_ltrpp ltr pthread gtest gtest_main)
target_link_libraries(func_ltrpp ltr pthread gtest gtest_main)

# Create testing target and redirect its output to `Testing` folder
add_test(NAME test_ltrpp COMMAND test_ltrpp WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
add_test(NAME func_ltrpp COMMAND func_ltrpp WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)

set_tests_properties(test_ltrpp
        PROPERTIES
        TIMEOUT 30
        ENVIRONMENT MOVIES_BENCHMARK=${MOVIES_BENCHMARK}
        )
set_tests_properties(func_ltrpp
        PROPERTIES
        TIMEOUT 30
        ENVIRONMENT MOVIES_BENCHMARK=${MOVIES_BENCHMARK}
        )

include(FindValgrind)

add_custom_target(valgrind_test_ltrpp
        COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:test_ltrpp>
        DEPENDS test_ltrpp
        )
add_custom_target(valgrind_func_ltrpp
        COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:func_ltrpp>
        DEPENDS func_ltrpp
        )