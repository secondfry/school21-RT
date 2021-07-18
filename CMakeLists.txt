cmake_minimum_required(VERSION 3.14)
project(school21-rtv1)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
  includes
  libft
)
link_directories(
  libft
)
add_executable(
  parser_test
  tests/parser_level_from_line_test.cc
  tests/parser_parse_test.cc
  tests/parser_check_arguments_test.cc
  tests/mocks.cc
  includes/parser.h
  srcs/parser.c
  srcs/parser_level.c
  srcs/parser_level_process.c
  srcs/parser_parse_1.c
  srcs/parser_parse_2.c
  srcs/graceful.c
)
target_link_libraries(
  parser_test
  gtest_main
  ft
)

include(GoogleTest)
gtest_discover_tests(parser_test)
