# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 11)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
add_compile_options(/EHsc)
add_compile_options(/permissive-)

project ("blackjack-plusplus")

# Include source
add_subdirectory("src")
target_include_directories(engine PUBLIC "./src")

# Include python bindings
set(PYTHON_LIBRARY_DIR "D:/Data/blackjack-plusplus/venv/Lib/site-packages")
set(PYTHON_EXECUTABLE "D:/Data/blackjack-plusplus/venv/Scripts/python")

add_subdirectory(extern/pybind11)
pybind11_add_module(blackjackplusplus python/engine.cpp)
target_include_directories(blackjackplusplus PUBLIC "./src")
target_link_libraries(blackjackplusplus PUBLIC engine)

# install(TARGETS blackjackplusplus DESTINATION ${PYTHON_LIBRARY_DIR})
add_custom_command(TARGET blackjackplusplus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:blackjackplusplus> ${PYTHON_LIBRARY_DIR}
)


# Include tests
add_subdirectory("tests")
target_include_directories(engine PUBLIC "./tests")

# Include examples
add_subdirectory("examples")
target_include_directories(engine PUBLIC "./examples")