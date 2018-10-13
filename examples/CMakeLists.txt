cmake_minimum_required(VERSION 2.8.0)

find_package(EXPAT REQUIRED)

include_directories (. .. ${EXPAT_INCLUDE_DIRS})

# SET(CMAKE_BUILD_TYPE Debug)

add_executable (gpxls gpxls.cpp)
target_link_libraries (gpxls gpx ${EXPAT_LIBRARIES})

add_executable (gpxwpt gpxwpt.cpp)
target_link_libraries (gpxwpt gpx ${EXPAT_LIBRARIES})

add_executable (gpxtrk gpxtrk.cpp)
target_link_libraries (gpxtrk gpx ${EXPAT_LIBRARIES})

add_executable (gpxi gpxi.cpp)
target_link_libraries (gpxi gpx ${EXPAT_LIBRARIES})

add_executable (gpxcsvtrk gpxcsvtrk.cpp)
target_link_libraries (gpxcsvtrk gpx ${EXPAT_LIBRARIES})

add_executable (gpxtest gpxtest.cpp)
target_link_libraries (gpxtest gpx ${EXPAT_LIBRARIES})

add_executable (gpxtrkcon gpxtrkcon.cpp)
target_link_libraries (gpxtrkcon gpx ${EXPAT_LIBRARIES})


