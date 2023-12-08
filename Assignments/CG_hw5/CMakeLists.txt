include(CMakeFiles.cmake)

add_executable(CG_hw5 ${CG_hw5_FILES})

set_target_properties(CG_hw5 PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CG_hw5 PUBLIC cxx_std_20)

target_include_directories(CG_hw5 PUBLIC "./src")

target_link_libraries(CG_hw5 PRIVATE slm CommandLineParser FileIO)