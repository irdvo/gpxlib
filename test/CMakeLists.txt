cmake_minimum_required(VERSION 2.9.0)

find_package(EXPAT REQUIRED)

include_directories (. .. ${EXPAT_INCLUDE_DIRS})

# SET(CMAKE_BUILD_TYPE Debug)

add_executable (gpxcheck gpxcheck.cpp)
target_link_libraries (gpxcheck gpx ${EXPAT_LIBRARIES})
set_target_properties(gpxcheck PROPERTIES CXX_STANDARD 11)
