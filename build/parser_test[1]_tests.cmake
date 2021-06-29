add_test( HelloTest.BasicAssertions /Users/oadhesiv/school21-rtv1/build/parser_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( HelloTest.BasicAssertions PROPERTIES WORKING_DIRECTORY /Users/oadhesiv/school21-rtv1/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( parser_test_TESTS HelloTest.BasicAssertions)
