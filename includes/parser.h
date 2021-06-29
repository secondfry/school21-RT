#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "array.h"
# include "defines.h"
# include "get_next_line.h"
# include "graceful.h"

# define LTYPE_UNSET	0
# define LTYPE_NODE	1
# define LTYPE_LEAF	2

typedef struct s_level {
	char			*key;
	char			*value;
	t_ptr_array		*data;
	t_byte			type;
	struct s_level	*parent;
	t_byte			offset;
}				t_level;

# define ERR_PARSER_NO_COLON "Line must either be filled with spaces which I disgrace because you should really not fill your configuration files with extra unneeded spaces but for some reason I have to workaround this exact condition...\n or have colon in it."

t_level	*level_from_line(const char *line);
void	parser(t_rtv *rtv, int fd);

#endif
