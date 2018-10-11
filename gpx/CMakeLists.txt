cmake_minimum_required(VERSION 2.8.0)

project(gpx)

find_package(EXPAT REQUIRED)

include_directories (. .. ${EXPAT_INCLUDE_DIRS})

# SET(CMAKE_BUILD_TYPE Debug)

set(SRC
    Node.cpp
    Decimal.cpp
    DateTime.cpp
    String.cpp
    Unsigned.cpp
    DGPSStation
    Fix.cpp
    Degrees.cpp
    Longitude.cpp
    Latitude.cpp
    Bounds.cpp
    PTSeg.cpp
    PT.cpp
    EMail.cpp
    Link.cpp
    Person.cpp
    URI.cpp
    Copyright.cpp
    TRKSeg.cpp
    Extensions.cpp
    TRK.cpp
    WPT.cpp
    RTE.cpp
    Metadata.cpp
    GPX.cpp
    Parser.cpp
    Writer.cpp
    Report.cpp
    ReportCerr.cpp
    )

option(BUILD_SHARED_LIBS "Build shared library" ON)
if(BUILD_SHARED_LIBS)
    add_definitions(-DBUILD_SHARED_LIBS)
    if(WIN32)
        add_definitions(-DDLL_EXPORT)
    endif()
endif()

add_library(gpx ${SRC})
target_link_libraries(gpx ${EXPAT_LIBRARIES})

set_target_properties(gpx PROPERTIES VERSION   1)
set_target_properties(gpx PROPERTIES SOVERSION 1)

install(TARGETS gpx RUNTIME DESTINATION bin
                    LIBRARY DESTINATION lib
                    ARCHIVE DESTINATION lib)

