include(CMakeFiles.cmake)

add_library(FileIO STATIC ${FileIO_FILES})

set_target_properties(FileIO PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(FileIO PUBLIC cxx_std_20)

target_include_directories(FileIO PUBLIC "./src")

target_precompile_headers(FileIO PUBLIC "./src/FileIOPCH.h")

add_subdirectory("tests")