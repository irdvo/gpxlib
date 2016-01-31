cmake_minimum_required(VERSION 2.6.0)

include_directories (. ..)

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
    )


# SHARED or STATIC
add_library(gpx
            STATIC
            ${SRC})
