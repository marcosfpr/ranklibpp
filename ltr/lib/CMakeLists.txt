find_package(Boost REQUIRED)

set(SOURCES
    impl/learning/DataPoint.cpp
    impl/learning/RankList.cpp
    impl/learning/Ranker.cpp
    impl/metric/MetricScorer.cpp
    impl/metric/MAPScorer.cpp
    impl/utils/KeyValue.cpp
    impl/utils/JsonParser.cpp

)

add_library(
    ltr
    ${SOURCES}
)

target_include_directories(
    ltr PUBLIC api PRIVATE
    ${Boost_INCLUDE_DIRS}
)


set_target_properties(
    ltr PROPERTIES PUBLIC_HEADER
    /api/ltr.hpp
)

set_target_properties(ltr PROPERTIES SOVERSION 1)

install(TARGETS ltr
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION api
)