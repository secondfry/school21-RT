#include "parser.h"

#define LTYPE_NODE	0
#define LTYPE_LEAF	1

typedef struct s_level {
	char		*key;
	char		*value;
	t_ptr_array	*data;
	t_byte		type;
	t_level		*parent;
}				t_level;

static t_byte	count_offset(char *line) {
	t_byte i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

static t_byte	get_type(char *line) {
	char **data = ft_strsplit(line, ':');
	t_byte i = 0;
	while (data[i]) {
		free(data[i]);
		i++;
	}
	free(data);
	if (i == 1) return LTYPE_NODE;
	if (i == 2) return LTYPE_LEAF;
	ft_putendl_fd("kurarek mnogo :::::::: bratan", 2);
	exit(0);
}

static char *get_key(char *line) {
	char **data = ft_strsplit(line, ':');
	char *ret = data[0];
	t_byte i = 1;
	while (data[i]) {
		free(data[i]);
		i++;
	}
	free(data);
	if (ft_strlen(ret) == 0 || ret[0] != '"' || ret[ft_strlen(ret) - 1] != '"') {
		ft_putendl_fd("key must start and end with \"", 2);
		exit(0);
	}
	return (ret);
}

static char *get_value(char *line) {
	char **data = ft_strsplit(line, ':');
	char *ret = data[1];
	free(data[0]);
	free(data);
	return (ret);
}

t_level	*level_new(t_level *parent, t_byte type) {
	t_level *ret;

	ret = (t_level *)malloc(sizeof(t_level));
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret->key = (void *)0;
	ret->data = ptr_array_new(10);
	ret->type = type;
	ret->parent = parent;
	return (ret);
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
	t_level	root = { 0, ptr_array_new(10), LTYPE_NODE, 0 };
	t_level *current = &root;
	t_byte offset_prev = 0;
	while (1) {
		int gnl_status = get_next_line(fd, &line);
		if (gnl_status == -1) {
			ft_putendl_fd("kurlyk gnl failed", 2);
			exit(1);
		}
		t_byte offset = count_offset(line);
		t_byte type = get_type(line);
		if (offset == offset_prev) {
			level_new(current, )
		}

		if (ft_strcmp(line, "lights:") == 0)
		 	read_lights(fd);
	}
}
