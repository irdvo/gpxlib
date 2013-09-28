include_directories (. ..)

add_executable (gpxls gpxls.cpp)
target_link_libraries (gpxls gpx expat)

add_executable (gpxwpt gpxwpt.cpp)
target_link_libraries (gpxwpt gpx expat)

