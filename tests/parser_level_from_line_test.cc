#include <gtest/gtest.h>

#define _Bool bool

extern "C" {
#include "parser.h"
}

// Valid cases

TEST(ParserLevelFromLineTest, EmptyLine) {
  std::string line("");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level, (void *)0);
}

TEST(ParserLevelFromLineTest, LineWithSpaces) {
  std::string line("    ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level, (void *)0);
}

TEST(ParserLevelFromLineTest, RootLineNode) {
  std::string line("hello:");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, RootLineNodeWithKeySuffixSpaces) {
  std::string line("hello     :");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, RootLineNodeWithSuffixSpaces) {
  std::string line("hello:    ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, RootLineNodeWithSpaces) {
  std::string line("hello    :    ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, LineNode) {
  std::string line("  hello:");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, LineNodeWithKeySuffixSpaces) {
  std::string line("  hello      :");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, LineNodeWithSuffixSpaces) {
  std::string line("  hello:   ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, LineNodeWithSpaces) {
  std::string line("  hello  :   ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_NODE);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, RootLineLeaf) {
  std::string line("hello: world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, RootLineLeafWithSuffixSpaces) {
  std::string line("hello: world  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineLeaf) {
  std::string line("  hello: world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineLeafWithKeySuffixSpaces) {
  std::string line("  hello          : world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineLeafWithSuffixSpaces) {
  std::string line("  hello: world  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineLeafWithSpaces) {
  std::string line("  hello : world  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "hello");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 2);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

// Questionable cases

TEST(ParserLevelFromLineTest, RootLineLeafWithInbetweenSpaces) {
  std::string line("h e l l o: w o r l d  ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_STREQ(level->key, "h e l l o");
  EXPECT_EQ(level->type, LTYPE_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "w o r l d");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineLeafWithInbetweenSpaces) {
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

TEST(ParserLevelFromLineTest, RootLineNoColon) {
  std::string line("hello");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserLevelFromLineTest, LineNoColon) {
  std::string line("   hello");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserLevelFromLineTest, RootLineNoColonWithSuffixSpaces) {
  std::string line("hello   ");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserLevelFromLineTest, RootLineNoColonWithInsideSpaces) {
  std::string line("h e l l o");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserLevelFromLineTest, RootLineNoColonWithSpaces) {
  std::string line("h e l l o   ");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}

TEST(ParserLevelFromLineTest, LineNoColonWithSpaces) {
  std::string line("   h e l l o   ");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_NO_COLON);
}
