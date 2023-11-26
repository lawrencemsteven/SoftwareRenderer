include(CMakeFiles.cmake)

add_executable(CG_hw4 ${CG_hw4_FILES})

set_target_properties(CG_hw4 PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CG_hw4 PUBLIC cxx_std_20)

target_include_directories(CG_hw4 PUBLIC "./src")

target_link_libraries(CG_hw4 PRIVATE slm CommandLineParser FileIO)