add_executable(scanner scanner_test.c)
target_link_libraries(scanner PRIVATE c_less_to_css)
add_test(NAME test_scanner COMMAND scanner)

add_executable(parser parser_test.c)
target_link_libraries(parser PRIVATE c_less_to_css)
add_test(NAME test_parser COMMAND parser)
