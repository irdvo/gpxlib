if(WIN32)
  set(EXPAT_FOUND TRUE)
  set(EXPAT_INCLUDE_DIRS "/Program Files (x86)/Expat 2.2.0/Source/lib")
  set(EXPAT_LIBRARIES    "/Program Files (x86)/Expat 2.2.0/Bin/libexpat")
  # Copy libexpat.dll and test.gpxto executable directory
else()
  find_package(EXPAT REQUIRED)
endif()

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


