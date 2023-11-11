include(CMakeFiles.cmake)

add_executable(CG_hw3 ${CG_hw3_FILES})

set_target_properties(CG_hw3 PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CG_hw3 PUBLIC cxx_std_20)

target_include_directories(CG_hw3 PUBLIC "./src")

target_link_libraries(CG_hw3 PRIVATE slm CommandLineParser FileIO)