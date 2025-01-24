add_executable(scanner scanner_test.c)
target_link_libraries(scanner PRIVATE less4c)
add_test(NAME test_scanner COMMAND scanner)

add_executable(parser parser_test.c)
target_link_libraries(parser PRIVATE less4c)
add_test(NAME test_parser COMMAND parser)

add_executable(transform transform_test.c)
target_link_libraries(transform PRIVATE less4c)
add_test(NAME test_transform COMMAND transform)
