project(gpx)

cmake_minimum_required(VERSION 2.8.0)

set (gpx_VERSION_MAJOR 0)
set (gpx_VERSION_MINOR 1)
set (gpx_VERSION_MICRO 1)

add_subdirectory(gpx)
option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif(BUILD_EXAMPLES)
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
	add_subdirectory(test)
endif()

install(DIRECTORY gpx/ DESTINATION include/gpx FILES_MATCHING PATTERN "*.h" PATTERN "CMakeFiles" EXCLUDE)

# uninstall:
# xargs rm <install_manifest.txt

