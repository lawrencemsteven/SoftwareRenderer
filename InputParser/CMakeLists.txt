include(CMakeFiles.cmake)

add_library(InputParser STATIC ${InputParser_FILES})

set_target_properties(InputParser PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(InputParser PUBLIC cxx_std_20)

target_include_directories(InputParser PUBLIC "./src")

target_precompile_headers(InputParser PUBLIC "./src/InputParserPCH.h")

add_subdirectory("tests")