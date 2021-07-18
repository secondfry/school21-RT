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
  char *memory = (char *)0;
  t_level *root = parse(fd, &memory);
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
  char *memory = (char *)0;

  t_level *root = parse(fd, &memory);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 5);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);
  
  t_level *light = (t_level *)root->data->data[0];
  EXPECT_EQ(light->offset, 0);
  EXPECT_EQ(light->child_offset, 2);
  EXPECT_EQ(light->data->used, 3);
  EXPECT_STREQ(light->key, "light");
  EXPECT_EQ(light->value, (void *)0);
  EXPECT_EQ(light->parent, root);
  EXPECT_EQ(light->type, LTYPE_NODE);
  
  t_level *point = (t_level *)light->data->data[0];
  EXPECT_EQ(point->offset, 2);
  EXPECT_EQ(point->child_offset, 4);
  EXPECT_EQ(point->data->used, 1);
  EXPECT_STREQ(point->key, "point");
  EXPECT_EQ(point->value, (void *)0);
  EXPECT_EQ(point->parent, light);
  EXPECT_EQ(point->type, LTYPE_NODE);
  
  t_level *point_0_list_node = (t_level *)point->data->data[0];
  EXPECT_EQ(point_0_list_node->offset, 4);
  EXPECT_EQ(point_0_list_node->child_offset, 6);
  EXPECT_EQ(point_0_list_node->data->used, 1);
  EXPECT_EQ(point_0_list_node->key, (void *)0);
  EXPECT_EQ(point_0_list_node->value, (void *)0);
  EXPECT_EQ(point_0_list_node->parent, point);
  EXPECT_EQ(point_0_list_node->type, LTYPE_LIST_NODE);
  
  t_level *point_0_root = (t_level *)point_0_list_node->data->data[0];
  EXPECT_EQ(point_0_root->offset, 6);
  EXPECT_EQ(point_0_root->child_offset, 6);
  EXPECT_EQ(point_0_root->data->used, 2);
  EXPECT_EQ(point_0_root->key, (void *)0);
  EXPECT_EQ(point_0_root->value, (void *)0);
  EXPECT_EQ(point_0_root->parent, point_0_list_node);
  EXPECT_EQ(point_0_root->type, LTYPE_NODE);
  
  t_level *point_0_position = (t_level *)point_0_root->data->data[0];
  EXPECT_EQ(point_0_position->offset, 6);
  EXPECT_EQ(point_0_position->child_offset, 8);
  EXPECT_EQ(point_0_position->data->used, 3);
  EXPECT_STREQ(point_0_position->key, "position");
  EXPECT_EQ(point_0_position->value, (void *)0);
  EXPECT_EQ(point_0_position->parent, point_0_root);
  EXPECT_EQ(point_0_position->type, LTYPE_NODE);
  
  t_level *point_0_position_x = (t_level *)point_0_position->data->data[0];
  EXPECT_EQ(point_0_position_x->offset, 8);
  EXPECT_EQ(point_0_position_x->child_offset, -1);
  EXPECT_EQ(point_0_position_x->data, (void *)0);
  EXPECT_STREQ(point_0_position_x->key, "x");
  EXPECT_STREQ(point_0_position_x->value, "2");
  EXPECT_EQ(point_0_position_x->parent, point_0_position);
  EXPECT_EQ(point_0_position_x->type, LTYPE_LEAF);
  
  t_level *point_0_position_y = (t_level *)point_0_position->data->data[1];
  EXPECT_EQ(point_0_position_y->offset, 8);
  EXPECT_EQ(point_0_position_y->child_offset, -1);
  EXPECT_EQ(point_0_position_y->data, (void *)0);
  EXPECT_STREQ(point_0_position_y->key, "y");
  EXPECT_STREQ(point_0_position_y->value, "1");
  EXPECT_EQ(point_0_position_y->parent, point_0_position);
  EXPECT_EQ(point_0_position_y->type, LTYPE_LEAF);
  
  t_level *point_0_position_z = (t_level *)point_0_position->data->data[2];
  EXPECT_EQ(point_0_position_z->offset, 8);
  EXPECT_EQ(point_0_position_z->child_offset, -1);
  EXPECT_EQ(point_0_position_z->data, (void *)0);
  EXPECT_STREQ(point_0_position_z->key, "z");
  EXPECT_STREQ(point_0_position_z->value, "0");
  EXPECT_EQ(point_0_position_z->parent, point_0_position);
  EXPECT_EQ(point_0_position_z->type, LTYPE_LEAF);
  
  t_level *point_0_intensity = (t_level *)point_0_root->data->data[1];
  EXPECT_EQ(point_0_intensity->offset, 6);
  EXPECT_EQ(point_0_intensity->child_offset, -1);
  EXPECT_EQ(point_0_intensity->data, (void *)0);
  EXPECT_STREQ(point_0_intensity->key, "intensity");
  EXPECT_STREQ(point_0_intensity->value, "60");
  EXPECT_EQ(point_0_intensity->parent, point_0_root);
  EXPECT_EQ(point_0_intensity->type, LTYPE_LEAF);
  
  t_level *directional = (t_level *)light->data->data[1];
  EXPECT_EQ(directional->offset, 2);
  EXPECT_EQ(directional->child_offset, 4);
  EXPECT_EQ(directional->data->used, 1);
  EXPECT_STREQ(directional->key, "directional");
  EXPECT_EQ(directional->value, (void *)0);
  EXPECT_EQ(directional->parent, light);
  EXPECT_EQ(directional->type, LTYPE_NODE);
  
  t_level *directional_0_list_node = (t_level *)directional->data->data[0];
  EXPECT_EQ(directional_0_list_node->offset, 4);
  EXPECT_EQ(directional_0_list_node->child_offset, 6);
  EXPECT_EQ(directional_0_list_node->data->used, 1);
  EXPECT_EQ(directional_0_list_node->key, (void *)0);
  EXPECT_EQ(directional_0_list_node->value, (void *)0);
  EXPECT_EQ(directional_0_list_node->parent, directional);
  EXPECT_EQ(directional_0_list_node->type, LTYPE_LIST_NODE);
  
  t_level *directional_0_root = (t_level *)directional_0_list_node->data->data[0];
  EXPECT_EQ(directional_0_root->offset, 6);
  EXPECT_EQ(directional_0_root->child_offset, 6);
  EXPECT_EQ(directional_0_root->data->used, 2);
  EXPECT_EQ(directional_0_root->key, (void *)0);
  EXPECT_EQ(directional_0_root->value, (void *)0);
  EXPECT_EQ(directional_0_root->parent, directional_0_list_node);
  EXPECT_EQ(directional_0_root->type, LTYPE_NODE);
  
  t_level *directional_0_position = (t_level *)directional_0_root->data->data[0];
  EXPECT_EQ(directional_0_position->offset, 6);
  EXPECT_EQ(directional_0_position->child_offset, 8);
  EXPECT_EQ(directional_0_position->data->used, 3);
  EXPECT_STREQ(directional_0_position->key, "direction");
  EXPECT_EQ(directional_0_position->value, (void *)0);
  EXPECT_EQ(directional_0_position->parent, directional_0_root);
  EXPECT_EQ(directional_0_position->type, LTYPE_NODE);
  
  t_level *directional_0_position_x = (t_level *)directional_0_position->data->data[0];
  EXPECT_EQ(directional_0_position_x->offset, 8);
  EXPECT_EQ(directional_0_position_x->child_offset, -1);
  EXPECT_EQ(directional_0_position_x->data, (void *)0);
  EXPECT_STREQ(directional_0_position_x->key, "x");
  EXPECT_STREQ(directional_0_position_x->value, "-1");
  EXPECT_EQ(directional_0_position_x->parent, directional_0_position);
  EXPECT_EQ(directional_0_position_x->type, LTYPE_LEAF);
  
  t_level *directional_0_position_y = (t_level *)directional_0_position->data->data[1];
  EXPECT_EQ(directional_0_position_y->offset, 8);
  EXPECT_EQ(directional_0_position_y->child_offset, -1);
  EXPECT_EQ(directional_0_position_y->data, (void *)0);
  EXPECT_STREQ(directional_0_position_y->key, "y");
  EXPECT_STREQ(directional_0_position_y->value, "4");
  EXPECT_EQ(directional_0_position_y->parent, directional_0_position);
  EXPECT_EQ(directional_0_position_y->type, LTYPE_LEAF);
  
  t_level *directional_0_position_z = (t_level *)directional_0_position->data->data[2];
  EXPECT_EQ(directional_0_position_z->offset, 8);
  EXPECT_EQ(directional_0_position_z->child_offset, -1);
  EXPECT_EQ(directional_0_position_z->data, (void *)0);
  EXPECT_STREQ(directional_0_position_z->key, "z");
  EXPECT_STREQ(directional_0_position_z->value, "-4");
  EXPECT_EQ(directional_0_position_z->parent, directional_0_position);
  EXPECT_EQ(directional_0_position_z->type, LTYPE_LEAF);
  
  t_level *directional_0_intensity = (t_level *)directional_0_root->data->data[1];
  EXPECT_EQ(directional_0_intensity->offset, 6);
  EXPECT_EQ(directional_0_intensity->child_offset, -1);
  EXPECT_EQ(directional_0_intensity->data, (void *)0);
  EXPECT_STREQ(directional_0_intensity->key, "intensity");
  EXPECT_STREQ(directional_0_intensity->value, "20");
  EXPECT_EQ(directional_0_intensity->parent, directional_0_root);
  EXPECT_EQ(directional_0_intensity->type, LTYPE_LEAF);
  
  t_level *sphere = (t_level *)root->data->data[1];
  EXPECT_EQ(sphere->offset, 0);
  EXPECT_EQ(sphere->child_offset, 2);
  EXPECT_EQ(sphere->data->used, 3);
  EXPECT_STREQ(sphere->key, "sphere");
  EXPECT_EQ(sphere->value, (void *)0);
  EXPECT_EQ(sphere->parent, root);
  EXPECT_EQ(sphere->type, LTYPE_NODE);
  
  t_level *sphere_0_list_node = (t_level *)sphere->data->data[0];
  EXPECT_EQ(sphere_0_list_node->offset, 2);
  EXPECT_EQ(sphere_0_list_node->child_offset, 4);
  EXPECT_EQ(sphere_0_list_node->data->used, 1);
  EXPECT_EQ(sphere_0_list_node->key, (void *)0);
  EXPECT_EQ(sphere_0_list_node->value, (void *)0);
  EXPECT_EQ(sphere_0_list_node->parent, sphere);
  EXPECT_EQ(sphere_0_list_node->type, LTYPE_LIST_NODE);
  
  t_level *sphere_0_root = (t_level *)sphere_0_list_node->data->data[0];
  EXPECT_EQ(sphere_0_root->offset, 4);
  EXPECT_EQ(sphere_0_root->child_offset, 4);
  EXPECT_EQ(sphere_0_root->data->used, 4);
  EXPECT_EQ(sphere_0_root->key, (void *)0);
  EXPECT_EQ(sphere_0_root->value, (void *)0);
  EXPECT_EQ(sphere_0_root->parent, sphere_0_list_node);
  EXPECT_EQ(sphere_0_root->type, LTYPE_NODE);
  
  t_level *sphere_0_position = (t_level *)sphere_0_root->data->data[0];
  t_level *sphere_0_color = (t_level *)sphere_0_root->data->data[1];
  t_level *sphere_0_color_red = (t_level *)sphere_0_color->data->data[0];
  EXPECT_EQ(sphere_0_color_red->offset, 6);
  EXPECT_EQ(sphere_0_color_red->child_offset, -1);
  EXPECT_EQ(sphere_0_color_red->data, (void *)0);
  EXPECT_STREQ(sphere_0_color_red->key, "red");
  EXPECT_STREQ(sphere_0_color_red->value, "255");
  EXPECT_EQ(sphere_0_color_red->parent, sphere_0_color);
  EXPECT_EQ(sphere_0_color_red->type, LTYPE_LEAF);
  
  t_level *sphere_1_list_node = (t_level *)sphere->data->data[1];
  EXPECT_EQ(sphere_1_list_node->offset, 2);
  EXPECT_EQ(sphere_1_list_node->child_offset, 4);
  EXPECT_EQ(sphere_1_list_node->data->used, 1);
  EXPECT_EQ(sphere_1_list_node->key, (void *)0);
  EXPECT_EQ(sphere_1_list_node->value, (void *)0);
  EXPECT_EQ(sphere_1_list_node->parent, sphere);
  EXPECT_EQ(sphere_1_list_node->type, LTYPE_LIST_NODE);
  
  t_level *sphere_1_root = (t_level *)sphere_1_list_node->data->data[0];
  EXPECT_EQ(sphere_1_root->offset, 4);
  EXPECT_EQ(sphere_1_root->child_offset, 4);
  EXPECT_EQ(sphere_1_root->data->used, 4);
  EXPECT_EQ(sphere_1_root->key, (void *)0);
  EXPECT_EQ(sphere_1_root->value, (void *)0);
  EXPECT_EQ(sphere_1_root->parent, sphere_1_list_node);
  EXPECT_EQ(sphere_1_root->type, LTYPE_NODE);
  
  t_level *sphere_1_position = (t_level *)sphere_1_root->data->data[0];
  t_level *sphere_1_color = (t_level *)sphere_1_root->data->data[1];
  t_level *sphere_1_color_red = (t_level *)sphere_1_color->data->data[1];
  EXPECT_EQ(sphere_1_color_red->offset, 6);
  EXPECT_EQ(sphere_1_color_red->child_offset, -1);
  EXPECT_EQ(sphere_1_color_red->data, (void *)0);
  EXPECT_STREQ(sphere_1_color_red->key, "green");
  EXPECT_STREQ(sphere_1_color_red->value, "255");
  EXPECT_EQ(sphere_1_color_red->parent, sphere_1_color);
  EXPECT_EQ(sphere_1_color_red->type, LTYPE_LEAF);

  close(fd);
}

TEST(ParserParseTest, ValidEmptyNode_0) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/empty_node_0.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); i++)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  char *memory = (char *)0;
  t_level *root = parse(fd, &memory);
  EXPECT_EQ(root->offset, -2);
  EXPECT_EQ(root->child_offset, 0);
  EXPECT_EQ(root->data->used, 1);
  EXPECT_EQ(root->key, (void *)0);
  EXPECT_EQ(root->value, (void *)0);
  EXPECT_EQ(root->parent, (void *)0);
  EXPECT_EQ(root->type, LTYPE_NODE);

  t_level *child = (t_level *)root->data->data[0];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, -1);
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
  char *memory = (char *)0;
  t_level *root = parse(fd, &memory);
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
  EXPECT_EQ(child->child_offset, -1);
  EXPECT_EQ(child->data->used, 0);
  EXPECT_STREQ(child->key, "empty");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_NODE);

  child = (t_level *)root->data->data[1];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, -1);
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
  char *memory = (char *)0;
  t_level *root = parse(fd, &memory);
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
  EXPECT_EQ(child->child_offset, -1);
  EXPECT_EQ(child->data, (void *)0);
  EXPECT_STREQ(child->key, "parent");
  EXPECT_STREQ(child->value, "something");
  EXPECT_EQ(child->parent, root);
  EXPECT_EQ(child->type, LTYPE_LEAF);

  child = (t_level *)root->data->data[1];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, -1);
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
  char *memory = (char *)0;
  t_level *root = parse(fd, &memory);
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
  EXPECT_EQ(child->child_offset, -1);
  EXPECT_EQ(child->data->used, 0);
  EXPECT_STREQ(child->key, "empty");
  EXPECT_EQ(child->value, (void *)0);
  EXPECT_EQ(child->parent, root->data->data[0]);
  EXPECT_EQ(child->type, LTYPE_NODE);

  child = (t_level *)root->data->data[1];
  EXPECT_EQ(child->offset, 0);
  EXPECT_EQ(child->child_offset, -1);
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
    char *memory = (char *)0;
    ASSERT_DEATH({ t_level *root = parse(fd, &memory); }, ERR_PARSER_INVALID_OFFSET);
    close(fd);
  }
}
