cmake_minimum_required(VERSION 3.0.0)
project(ltrpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CPACK_PACKAGE_NAME "ltrpp")
set(CPACK_PACKAGE_RELEASE 1)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -O0")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

link_libraries(stdc++fs)

add_subdirectory(ltr)
add_subdirectory(external/googletest)

enable_testing()
add_subdirectory(tests)

add_subdirectory(docs)

find_program(GCOV gcov)
find_program(LCOV lcov)
find_program(GENHTML genhtml)
if(NOT GCOV)
  message(FATAL_ERROR "gcov not found!")
endif()
if(NOT LCOV)
  message(FATAL_ERROR "lcov not found!")
endif()
if(NOT GENHTML)
  message(FATAL_ERROR "genhtml not found!")
endif()

add_custom_target(gcov
  COMMAND mkdir -p Coverage
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Testing
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET gcov POST_BUILD
  COMMAND find ${CMAKE_BINARY_DIR} -type f -name *.cpp.o -exec ${GCOV} {} "\;"
  COMMAND echo "Coverage reports generated."
  COMMAND echo "You can find them on ${CMAKE_BINARY_DIR}/Coverage"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage
  COMMENT "Coverage Reports Generated"
)

add_custom_target(lcov
  COMMAND mkdir -p Coverage
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Testing
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET lcov POST_BUILD
  COMMAND ${LCOV} --directory .. --capture --output-file lcov.info
  COMMAND ${GENHTML} -o . lcov.info
  COMMAND echo "Coverage reports generated."
  COMMAND echo "You can find them on ${CMAKE_BINARY_DIR}/Coverage"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage
  COMMENT "Coverage Reports Generated"
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES Coverage)
