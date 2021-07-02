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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
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
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "w o r l d");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, RootLineListLeaf) {
  std::string line("- world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level->key, (void *)0);
  EXPECT_EQ(level->type, LTYPE_LIST_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, RootLineListLeafWithSpaces) {
  std::string line("-         w o r l d   ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level->key, (void *)0);
  EXPECT_EQ(level->type, LTYPE_LIST_LEAF);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "w o r l d");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineListLeaf) {
  std::string line("    - world");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level->key, (void *)0);
  EXPECT_EQ(level->type, LTYPE_LIST_LEAF);
  EXPECT_EQ(level->offset, 4);
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "world");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, LineListLeafWithSpaces) {
  std::string line("    -       w o r l d   ");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level->key, (void *)0);
  EXPECT_EQ(level->type, LTYPE_LIST_LEAF);
  EXPECT_EQ(level->offset, 4);
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_STREQ(level->value, "w o r l d");
  EXPECT_EQ(level->data, (void *)0);
}

TEST(ParserLevelFromLineTest, RootLineListNode) {
  std::string line("- skip: kripp");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level->key, (void *)0);
  EXPECT_EQ(level->type, LTYPE_LIST_NODE);
  EXPECT_EQ(level->offset, 0);
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
}

TEST(ParserLevelFromLineTest, LineListNode) {
  std::string line("                - skip: kripp");
  t_level *level = level_from_line(line.c_str());
  EXPECT_EQ(level->key, (void *)0);
  EXPECT_EQ(level->type, LTYPE_LIST_NODE);
  EXPECT_EQ(level->offset, 16);
  EXPECT_EQ(level->child_offset, 0);
  EXPECT_EQ(level->parent, (void *)0);
  EXPECT_EQ(level->value, (void *)0);
  EXPECT_EQ(level->data->used, 0);
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

TEST(ParserLevelFromLineTest, RootLineListNothingness) {
  std::string line("-");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_OADYAML_LIST_NAN);
}

TEST(ParserLevelFromLineTest, RootLineListNothingnessWithSpaces) {
  std::string line("-       ");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_OADYAML_LIST_NAN);
}

TEST(ParserLevelFromLineTest, LineListNothingness) {
  std::string line("           -");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_OADYAML_LIST_NAN);
}

TEST(ParserLevelFromLineTest, LineListNothingnessWithSpaces) {
  std::string line("           -  ");
  ASSERT_DEATH({ level_from_line(line.c_str()); }, ERR_PARSER_OADYAML_LIST_NAN);
}
