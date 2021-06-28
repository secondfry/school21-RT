#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "array.h"
# include "defines.h"
# include "get_next_line.h"
# include "graceful.h"

void	parser(t_rtv *rtv, int fd);

#endif
