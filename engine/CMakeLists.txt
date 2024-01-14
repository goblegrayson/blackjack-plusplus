# CMakeList.txt : CMake project for engine, include source and define
# project specific logic here.
#

# Include dependencies
include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)
FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Include sub-projects.
add_subdirectory ("test")

# create target
add_library(
    engine STATIC
    card.cpp
    shoe.cpp
    engine.hpp
    player.cpp
    hand.cpp
    round.cpp
    table.cpp
    strategies.cpp
)
target_link_libraries(engine PUBLIC matplot)

# Removing this for now because getting the dependencies built is a whole thing
# target_link_libraries(engine PRIVATE rtnorm)