set(OHSUMED "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/OHSUMED")

add_executable(
        ohsumed
        ohsumed/main.cpp
)

target_link_libraries(ohsumed ltr spdlog pthread)