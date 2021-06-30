#include <gtest/gtest.h>

#define _Bool bool

extern "C" {
#include "parser.h"
}

// Valid cases

// TEST(ParserParseTest, Valid) {
//   std::vector<std::string> args {"./RTv1", "tests/scenes/empty.yaml"};
//   std::vector<char *> argv;
//   argv.reserve(args.size());
//   for(size_t i = 0; i < args.size(); ++i)
//     argv.push_back(const_cast<char*>(args[i].c_str()));

//   t_rtv rtv;
//   parse(&rtv, args.size(), &argv[0]);
// }

// Questionable cases

// Invalid cases

TEST(ParserParseTest, InvalidEmptyNode) {
  std::vector<std::string> args {"./RTv1", "tests/scenes/invalid_0.oadyaml"};
  std::vector<char *> argv;
  argv.reserve(args.size());
  for(size_t i = 0; i < args.size(); ++i)
    argv.push_back(const_cast<char*>(args[i].c_str()));

  int fd = check_arguments(args.size(), &argv[0]);
  ASSERT_DEATH({ t_level *root = parse(fd); }, ERR_PARSER_EMPTY_NODE);
}
