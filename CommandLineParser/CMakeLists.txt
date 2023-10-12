include(CMakeFiles.cmake)

add_library(CommandLineParser STATIC ${CommandLineParser_FILES})

set_target_properties(CommandLineParser PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CommandLineParser PUBLIC cxx_std_20)

target_include_directories(CommandLineParser PUBLIC "./src")

target_precompile_headers(CommandLineParser PUBLIC "./src/CommandLineParserPCH.h")

add_subdirectory("tests")