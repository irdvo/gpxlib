include_directories (. ..)

add_executable (gpxls gpxls.cpp)
target_link_libraries (gpxls gpx expat)

add_executable (gpxwpt gpxwpt.cpp)
target_link_libraries (gpxwpt gpx expat)

add_executable (gpxtrk gpxtrk.cpp)
target_link_libraries (gpxtrk gpx expat)

# SET(CMAKE_BUILD_TYPE Debug)
add_executable (gpxi gpxi.cpp)
target_link_libraries (gpxi gpx expat)

add_executable (gpxcsvtrk gpxcsvtrk.cpp)
target_link_libraries (gpxcsvtrk gpx expat)


