cmake_minimum_required(VERSION 3.15)
enable_testing()

include(FetchContent)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(SoftwareRenderer)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.3.2
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)

FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(glm)

add_subdirectory("CommandLineParser")
add_subdirectory("FileIO")
add_subdirectory("slm")

add_subdirectory("Assignments/CG_hw1")
add_subdirectory("Assignments/CG_hw2")
add_subdirectory("Assignments/CG_hw3")
add_subdirectory("Assignments/CG_hw4")
add_subdirectory("Assignments/CG_hw5")