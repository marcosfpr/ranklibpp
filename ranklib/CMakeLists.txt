find_package(spdlog REQUIRED)

add_executable(
    ranklib
    ${PROJECT_SOURCE_DIR}/ranklib/RankLib.cpp
    ${PROJECT_SOURCE_DIR}/ranklib/src/impl/DataPoint.cpp
    ${PROJECT_SOURCE_DIR}/ranklib/src/impl/RankList.cpp
)

target_include_directories(
    ranklib PUBLIC
    api
    ${SPDLOG_INCLUDE_DIRS}
)

set_target_properties(
    ranklib PROPERTIES PUBLIC_HEADER
    RankLib.h 
)

set_target_properties(ranklib PROPERTIES SOVERSION 1)

install(TARGETS ranklib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION api
)