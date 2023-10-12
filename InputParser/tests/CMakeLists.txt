include(CMakeFiles.cmake)

add_executable(InputParser_unit_tests ${InputParser_test_FILES})

target_link_libraries(InputParser_unit_tests PRIVATE InputParser Catch2::Catch2WithMain)

set_target_properties(InputParser PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(InputParser_unit_tests PRIVATE cxx_std_20)

enable_testing()
add_test(NAME InputParser_unit_tests COMMAND $<TARGET_FILE:InputParser_unit_tests>)