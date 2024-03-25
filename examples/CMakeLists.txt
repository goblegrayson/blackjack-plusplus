target_include_directories(engine PUBLIC "../src")

# Add the playRound executable
add_executable(playRound
    playRound.cpp)
target_link_libraries(playRound PRIVATE engine)

# Add the StudyRound executable
add_executable(studyRound
    studyRound.cpp)
target_link_libraries(studyRound PRIVATE engine)