cmake_minimum_required(VERSION 3.0.0)
project(ranklibpp VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

find_package(spdlog REQUIRED)

set(CPACK_PACKAGE_NAME "ranklibcpp")
set(CPACK_PACKAGE_RELEASE 1)

add_executable(
    ${PROJECT_NAME} main.cpp
    ${PROJECT_SOURCE_DIR}/src/impl/DataPoint.cpp
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    /src/api
    /src/impl
    ${SPDLOG_INCLUDE_DIRS}
)

link_libraries(
    ${PROJECT_NAME}
    ${SPDLOG_LIBRARIES}
)


include(CPack)