include(CMakeFiles.cmake)

add_executable(CG_hw2unit_tests ${CG_hw2test_FILES})

target_link_libraries(CG_hw2unit_tests PRIVATE slm Catch2::Catch2WithMain)

set_target_properties(CG_hw2unit_tests PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(CG_hw2unit_tests PRIVATE cxx_std_20)

target_compile_definitions(CG_hw2unit_tests PRIVATE TEST_ASSETS_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/assets" )

enable_testing()
add_test(NAME CG_hw2unit_tests COMMAND $<TARGET_FILE:CG_hw2unit_tests>)