cmake_minimum_required(VERSION 2.9.0)

find_package(EXPAT REQUIRED)

include_directories (. .. ${EXPAT_INCLUDE_DIRS})

# SET(CMAKE_BUILD_TYPE Debug)

function(add_example name)
	add_executable (${name} ${name}.cpp)
	target_link_libraries (${name} gpx ${EXPAT_LIBRARIES})
	set_target_properties(${name} PROPERTIES CXX_STANDARD 11)
endfunction()

add_example(gpxls)
add_example(gpxwpt)
add_example(gpxtrk)
add_example(gpxi)
add_example(gpxcsvtrk)
add_example(gpxtest)
add_example(gpxtrkcon)
