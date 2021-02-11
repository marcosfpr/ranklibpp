find_package(Boost REQUIRED)

set(SOURCES
    impl/DataPoint.cpp
    impl/RankList.cpp
)

add_library(
    ranklib
    ${SOURCES}
)

target_include_directories(
    ranklib PUBLIC api PRIVATE
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(
    ranklib PROPERTIES PUBLIC_HEADER
    /api/ranklib.hpp
)

set_target_properties(ranklib PROPERTIES SOVERSION 1)

install(TARGETS ranklib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION api
)