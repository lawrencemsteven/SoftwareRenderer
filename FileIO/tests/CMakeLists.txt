include(CMakeFiles.cmake)

add_executable(FileIO_unit_tests ${FileIO_test_FILES})

target_link_libraries(FileIO_unit_tests PRIVATE FileIO Catch2::Catch2WithMain)

set_target_properties(FileIO_unit_tests PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(FileIO_unit_tests PRIVATE cxx_std_20)

target_compile_definitions(FileIO_unit_tests PRIVATE TEST_ASSETS_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/assets" )

enable_testing()
add_test(NAME FileIO_unit_tests COMMAND $<TARGET_FILE:FileIO_unit_tests>)