# CMakeList.txt : CMake project for engine, include source and define
# project specific logic here.
#


# Include sub-projects.
add_subdirectory ("test")

# create target
add_library(
    engine STATIC
    card.cpp
    shoe.cpp
    engine.hpp
)