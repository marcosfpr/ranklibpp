find_package(Boost COMPONENTS log log_setup REQUIRED)

add_definitions(-DBOOST_LOG_DYN_LINK)

set(SOURCES
    impl/learning/DataPoint.cpp
    impl/learning/RankList.cpp
    impl/learning/DataSet.cpp
    impl/learning/Ranker.cpp
    impl/learning/Learner.cpp
    impl/learning/ensemble/AdaRank.cpp
    impl/metric/MetricScorer.cpp
    impl/metric/MAPScorer.cpp
    impl/metric/PrecisionScorer.cpp
    impl/utils/KeyValue.cpp
    impl/utils/Logging.cpp
)

add_library(
    ltr SHARED
    ${SOURCES}
)

target_include_directories(
    ltr PUBLIC api PRIVATE
    ${Boost_INCLUDE_DIRS}
)

# logging stuff
target_link_libraries(ltr ${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY})

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
