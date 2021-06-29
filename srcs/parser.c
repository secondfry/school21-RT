#include "parser.h"

static t_byte	count_offset(char *line) {
	t_byte i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

t_level	*level_new() {
	t_level *ret;

	ret = (t_level *)malloc(sizeof(t_level));
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret->key = (void *)0;
	ret->type = LTYPE_UNSET;
	ret->parent = (void *)0;
	ret->value = (void *)0;
	ret->data = (void *)0;
	return (ret);
}

t_level	*level_from_line(const char *line) {
	t_level	*ret;

	t_byte i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 0)
		return (0);
	t_byte offset = i;
	while (line[i] && line[i] != ':')
		i++;
	if (line[i] == 0)
		check(1, 1, ERR_PARSER_NO_COLON);
	t_byte key_len = i - offset;
	char *key = ft_strsub(line, offset, key_len);
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	ret = level_new();
	ret->key = key;
	ret->offset = offset;
	if (line[i] == 0)
	{
		ret->type = LTYPE_NODE;
		ret->data = ptr_array_new(10);
	}
	else
	{
		ret->type = LTYPE_LEAF;
		t_byte q = ft_strlen(line) - 1;
		while (line[q] == ' ')
			q--;
		q++;
		ret->value = ft_strsub(line, i, q - i);
	}

	return ret;
}

static void read_lights(int fd)
{
	static t_byte status;
	char *line;

	if (status == 1) {
		ft_putendl_fd("kurlyk lights already read", 2);
		exit(1);
	}
	while (1) {
		int gnl_status = get_next_line(fd, &line);
		if (gnl_status == -1) {
			ft_putendl_fd("kurlyk gnl failed", 2);
			exit(1);
		}
		if (ft_strcmp(line, "lights:") == 0)
		 	read_lights(fd);
	}
}

void	parse(t_rtv *rtv, int argc, char **argv)
{
	(void)rtv;
	if (argc != 2) {
		ft_putendl_fd("kurlyk 2 argumenta", 2);
		exit(1);
	}
	int fd = open(argv[argc - 1], O_RDONLY);
	if (fd < 0) {
		ft_putendl_fd("kurlyk open failed", 2);
		exit(1);
	}
	int read_status = read(fd, 0, 0);
	if (read_status < 0) {
		ft_putendl_fd("kurlyk read failed", 2);
		exit(1);
	}
	char *line;
	t_level	*root = level_new();
	root->type = LTYPE_NODE;
	t_level *current = root;
	t_byte offset_prev = 0;
	while (1) {
		int gnl_status = get_next_line(fd, &line);
		if (gnl_status == -1) {
			ft_putendl_fd("kurlyk gnl failed", 2);
			exit(1);
		}
		// if (offset == offset_prev) {
		// 	level_new(current, )
		// }

		if (ft_strcmp(line, "lights:") == 0)
		 	read_lights(fd);
	}
}
