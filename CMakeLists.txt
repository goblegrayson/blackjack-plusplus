# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("blackjack-plusplus")

# Include sub-projects.
add_subdirectory ("engine")
target_include_directories(engine PUBLIC "./engine")

# Add the playRound executable
add_executable (playRound
    playRound.cpp)
target_link_libraries(playRound PRIVATE engine)

# Add the StudyRound executable
add_executable (studyRound
    studyRound.cpp)
target_link_libraries(studyRound PRIVATE engine)