#include <gtest/gtest.h>

#define _Bool bool

extern "C" {
#include "parser.h"
}

// Valid cases

TEST(ParserCheckArgumentsTest, Valid) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); ++i)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  EXPECT_GT(fd, 0);
  close(fd);
}

// Questionable cases

// Invalid cases

TEST(ParserCheckArgumentsTest, InvalidOneArg) {
  std::vector<std::string> args {"./RTv1"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); ++i)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  ASSERT_DEATH({ check_arguments(args.size(), &argv[0]); }, ERR_PARSER_ARGC);
}

TEST(ParserCheckArgumentsTest, InvalidThreeArgs) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty.yaml", "kripp"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); ++i)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  ASSERT_DEATH({ check_arguments(args.size(), &argv[0]); }, ERR_PARSER_ARGC);
}

TEST(ParserCheckArgumentsTest, InvalidFileDoesNotExist) {
  std::vector<std::string> args {"./RTv1", "/loboq"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); ++i)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  ASSERT_DEATH({ check_arguments(args.size(), &argv[0]); }, ERR_PARSER_OPEN);
}

TEST(ParserCheckArgumentsTest, InvalidFileIsDirectory) {
  std::vector<std::string> args {"./RTv1", "tests/scenes"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); ++i)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  ASSERT_DEATH({ check_arguments(args.size(), &argv[0]); }, ERR_PARSER_READ);
}
