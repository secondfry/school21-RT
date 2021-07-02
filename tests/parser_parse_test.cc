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
  t_level *root = parse(fd, (char *)0);
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
  t_level *root = parse(fd, (char *)0);
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

TEST(ParserParseTest, ValidEmptyNode_0) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty_node_0.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  t_level *root = parse(fd, (char *)0);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 1);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);

  t_level *child = (t_level *)root->data->data[0];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data->used, 0);
  EXPECT_STREQ(child->key, "empty");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_NODE);
  close(fd);
}

TEST(ParserParseTest, ValidEmptyNode_1) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty_node_1.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  t_level *root = parse(fd, (char *)0);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 2);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);

  t_level *child;

  child = (t_level *)root->data->data[0];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data->used, 0);
  EXPECT_STREQ(child->key, "empty");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_NODE);

  child = (t_level *)root->data->data[1];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data, (void *)0);
  EXPECT_STREQ(child->key, "parent");
  EXPECT_STREQ(child->value, "something");
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_LEAF);
  close(fd);
}

TEST(ParserParseTest, ValidEmptyNode_2) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty_node_2.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  t_level *root = parse(fd, (char *)0);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 2);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);

  t_level *child;

  child = (t_level *)root->data->data[0];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data, (void *)0);
  EXPECT_STREQ(child->key, "parent");
  EXPECT_STREQ(child->value, "something");
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_LEAF);

  child = (t_level *)root->data->data[1];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data->used, 0);
  EXPECT_STREQ(child->key, "empty");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_NODE);

  close(fd);
}

TEST(ParserParseTest, ValidEmptyNode_3) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty_node_3.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  t_level *root = parse(fd, (char *)0);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 2);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);

  t_level *child;

  child = (t_level *)root->data->data[0];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 2);
  EXPECT_EQ(child->data->used, 1);
  EXPECT_STREQ(child->key, "parent");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_NODE);

  child = (t_level *)child->data->data[0];
  EXPECT_EQ(child->offset, 2);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data->used, 0);
  EXPECT_STREQ(child->key, "empty");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root->data->data[0]);
  EXPECT_EQ(child->type, LTYPE_NODE);

  child = (t_level *)root->data->data[1];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, 0);
  EXPECT_EQ(child->data, (void *)0);
  EXPECT_STREQ(child->key, "parent");
  EXPECT_STREQ(child->value, "something");
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_LEAF);

  close(fd);
}

// Questionable cases

// Invalid cases

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
    ASSERT_DEATH({ t_level *root = parse(fd, (char *)0); }, ERR_PARSER_INVALID_OFFSET);
    close(fd);
  }
}
