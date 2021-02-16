# gpxlib

A c++ library for parsing, browsing, changing and writing of GPX files.

See [gpxlib](http://irdvo.nl/gpxlib) for more information.


## Building

After cloning the project, goto the project build directory: 

`cd gpxlib/build`

Run cmake for linux:

`cmake ..`

Run cmake for MinGW:

`cmake -G "MinGW Makefiles" ..`

Building static library:

`cmake -DBUILD_SHARED_LIBS=OFF ..`

Building dynamic library:

`cmake -DBUILD_SHARED_LIBS=ON ..`


## Tests

In the directory gpxlib/test there is test program (gpxtest).


## Examples

In the directory gpxlib/examples there are a few example programs.



