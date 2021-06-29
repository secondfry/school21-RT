#include <gtest/gtest.h>

#define _Bool bool

extern "C" {
#include "parser.h"
}

// Valid cases

TEST(ParserTestLevelFromLine, EmptyLine) {
  std::string line("");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level, (void *)0);
}

TEST(ParserTestLevelFromLine, LineWithSpaces) {
  std::string line("    ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level, (void *)0);
}

TEST(ParserTestLevelFromLine, RootLineNode) {
  std::string line("hello:");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserTestLevelFromLine, RootLineNodeWithSuffixSpaces) {
  std::string line("hello:    ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserTestLevelFromLine, LineNode) {
  std::string line("  hello:");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserTestLevelFromLine, LineNodeWithSuffixSpaces) {
  std::string line("  hello:   ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserTestLevelFromLine, RootLineLeaf) {
  std::string line("hello: world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserTestLevelFromLine, RootLineLeafWithSuffixSpaces) {
  std::string line("hello: world  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserTestLevelFromLine, LineLeaf) {
  std::string line("  hello: world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserTestLevelFromLine, LineLeafWithSuffixSpaces) {
  std::string line("  hello: world  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

// Questionable cases

TEST(ParserTestLevelFromLine, RootLineLeafWithInbetweenSpaces) {
  std::string line("h e l l o: w o r l d  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "h e l l o");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "w o r l d");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserTestLevelFromLine, LineLeafWithInbetweenSpaces) {
  std::string line("  h e l l o: w o r l d  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "h e l l o");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "w o r l d");
  EXPECT_EQ(level->data, (void *)0);
}

// Invalid cases

TEST(ParserTestLevelFromLine, RootLineNoColon) {
  std::string line("hello");
  ASSERT_DEATH( { level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserTestLevelFromLine, LineNoColon) {
  std::string line("   hello");
  ASSERT_DEATH( { level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserTestLevelFromLine, RootLineNoColonWithSuffixSpaces) {
  std::string line("hello   ");
  ASSERT_DEATH( { level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserTestLevelFromLine, RootLineNoColonWithInsideSpaces) {
  std::string line("h e l l o");
  ASSERT_DEATH( { level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserTestLevelFromLine, RootLineNoColonWithSpaces) {
  std::string line("h e l l o   ");
  ASSERT_DEATH( { level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserTestLevelFromLine, LineNoColonWithSpaces) {
  std::string line("   h e l l o   ");
  ASSERT_DEATH( { level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}
