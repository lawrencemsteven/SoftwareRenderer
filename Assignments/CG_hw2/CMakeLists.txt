include(CMakeFiles.cmake)

add_executable(CG_hw2 ${CG_hw2_FILES})

set_target_properties(CG_hw2 PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CG_hw2 PUBLIC cxx_std_20)

target_include_directories(CG_hw2 PUBLIC "./src")

target_link_libraries(CG_hw2 PRIVATE slm CommandLineParser FileIO)