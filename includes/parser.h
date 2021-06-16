#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "defines.h"
# include "get_next_line.h"
# include "error.h"

void	parser(t_wolf *wolf, int fd);

#endif
