#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "defines.h"
# include "get_next_line.h"

void	parser(t_rtv *rtv, int fd);

#endif
