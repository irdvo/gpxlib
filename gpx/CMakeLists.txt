cmake_minimum_required(VERSION 2.9.0)

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
    Algorithm.cpp
    )

option(BUILD_SHARED_LIBS "Build shared library" ON)
if(BUILD_SHARED_LIBS)
    add_definitions(-DBUILD_SHARED_LIBS)
    if(WIN32)
        add_definitions(-DDLL_EXPORT)
    endif()
endif()

add_library(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${EXPAT_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${BUILD_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin
                    LIBRARY DESTINATION lib
                    ARCHIVE DESTINATION lib)

