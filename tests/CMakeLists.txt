﻿# Testing library
add_executable (engine-tests
    main.cpp
    main.hpp
    catch_amalgamated.cpp
    catch_amalgamated.hpp
)

# Include test
target_include_directories(engine-tests PUBLIC "../src")
target_link_libraries(engine-tests PRIVATE engine)

# Add source to this project's executable.
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET engine-tests PROPERTY CXX_STANDARD 20)
endif()