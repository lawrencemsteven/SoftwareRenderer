include(CMakeFiles.cmake)

add_executable(slm_unit_tests ${slm_test_FILES})

target_link_libraries(slm_unit_tests PRIVATE slm Catch2::Catch2WithMain)

set_target_properties(slm_unit_tests PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(slm_unit_tests PRIVATE cxx_std_20)

target_compile_definitions(slm_unit_tests PRIVATE TEST_ASSETS_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/assets" )

enable_testing()
add_test(NAME slm_unit_tests COMMAND $<TARGET_FILE:slm_unit_tests>)