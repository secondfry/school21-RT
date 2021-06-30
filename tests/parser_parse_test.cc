#include <gtest/gtest.h>

#define _Bool bool

extern "C" {
#include "parser.h"
}

// Valid cases

TEST(ParserParseTest, ValidEmpty) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  t_level *root = parse(fd);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, -2);
  EXPECT_EQ(root->data->used, 0);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);
  close(fd);
}

TEST(ParserParseTest, ValidFull) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/full.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  t_level *root = parse(fd);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 5);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);
  // add more checks
  close(fd);
}

// Questionable cases

// Invalid cases

TEST(ParserParseTest, InvalidEmptyNode) {
  for (size_t i = 0; i < 4; i++) {
    char buffer[100];
    sprintf(buffer, "tests/scenes/invalid_empty_node_%zu.oadyaml", i);
    std::vector<std::string> args {"./RTv1", buffer};
    std::vector<char *> argv;
    argv.reserve(args.size());
    for(size_t i = 0; i < args.size(); i++)
      argv.push_back(const_cast<char*>(args[i].c_str()));

    int fd = check_arguments(args.size(), &argv[0]);
    // t_level *root = parse(fd);
    ASSERT_DEATH({ t_level *root = parse(fd); }, ERR_PARSER_EMPTY_NODE);
    close(fd);
  }
}

TEST(ParserParseTest, InvalidOffset) {
  for (size_t i = 0; i < 1; i++) {
    char buffer[100];
    sprintf(buffer, "tests/scenes/invalid_offset_%zu.oadyaml", i);
    std::vector<std::string> args {"./RTv1", buffer};
    std::vector<char *> argv;
    argv.reserve(args.size());
    for(size_t i = 0; i < args.size(); i++)
      argv.push_back(const_cast<char*>(args[i].c_str()));

    int fd = check_arguments(args.size(), &argv[0]);
    ASSERT_DEATH({ t_level *root = parse(fd); }, ERR_PARSER_INVALID_OFFSET);
    close(fd);
  }
}
