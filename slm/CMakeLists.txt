include(CMakeFiles.cmake)

add_library(slm STATIC ${slm_FILES})

set_target_properties(slm PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(slm PUBLIC cxx_std_20)

target_include_directories(slm PUBLIC "./src")

target_precompile_headers(slm PUBLIC "./src/slmPCH.h")

target_link_libraries(slm PUBLIC glm FileIO)

add_subdirectory("tests")