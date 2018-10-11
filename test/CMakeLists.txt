#if(WIN32)
#  set(EXPAT_FOUND TRUE)
#  set(EXPAT_INCLUDE_DIRS "/Program Files (x86)/Expat 2.2.0/Source/lib")
#  set(EXPAT_LIBRARIES    "/Program Files (x86)/Expat 2.2.0/Bin/libexpat")
  # Copy libexpat.dll and test.gpx to executable directory
#else()
  find_package(EXPAT REQUIRED)
#endif()

include_directories (. .. ${EXPAT_INCLUDE_DIRS})

# SET(CMAKE_BUILD_TYPE Debug)

add_executable (gpxcheck gpxcheck.cpp)
target_link_libraries (gpxcheck gpx ${EXPAT_LIBRARIES})

