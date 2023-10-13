include(CMakeFiles.cmake)

add_executable(CG_hw1 ${CG_hw1_FILES})

set_target_properties(CG_hw1 PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CG_hw1 PUBLIC cxx_std_20)

target_include_directories(CG_hw1 PUBLIC "./src")

target_link_libraries(CG_hw1 PRIVATE slm CommandLineParser FileIO)