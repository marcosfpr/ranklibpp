find_package(Boost REQUIRED)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/ranklib/RankLib.cpp
    ${PROJECT_SOURCE_DIR}/ranklib/src/impl/DataPoint.cpp
    ${PROJECT_SOURCE_DIR}/ranklib/src/impl/RankList.cpp
)

add_executable(
    ranklib
    ${SOURCES}
)

target_include_directories(
    ranklib PUBLIC
    api
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(
    ranklib PROPERTIES PUBLIC_HEADER
    RankLib.h 
)

set_target_properties(ranklib PROPERTIES SOVERSION 1)
