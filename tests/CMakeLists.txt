find_package(Check REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

# Since Check uses Threads to paralelize the tests, it's mandatory
# add pthread as a dependency, alongside the Check libraries.
add_executable(
  test_ranklib
  unit/DataPointTest.cpp
)

target_link_libraries(test_ranklib ${CHECK_LIBRARIES} pthread)

# Create testing target and redirect its output to `Testing` folder
add_test(NAME test_ranklib COMMAND test_ranklib WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ranklib)
set_tests_properties(test_ranklib PROPERTIES TIMEOUT 30) 

# Aditional Valgrind test to check memory leaks in code
include(FindValgrind)

add_custom_target(valgrind_test_ranklib
  COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:test_ranklib>
  DEPENDS test_ranklib
)