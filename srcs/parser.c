#include "parser.h"

t_level	*level_new()
{
	t_level *ret;

	ret = (t_level *)malloc(sizeof(t_level));
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret->key = (void *)0;
	ret->type = LTYPE_UNSET;
	ret->parent = (void *)0;
	ret->value = (void *)0;
	ret->data = (void *)0;
	ret->offset = 0;
	ret->child_offset = 0;
	return (ret);
}

void validate(t_rtv *rtv, t_level *root)
{
	(void)rtv;
	(void)root;
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
	t_byte q = i - 1;
	while (line[q] == ' ')
		q--;
	q++;
	t_byte key_len = q - offset;
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

int check_arguments(int argc, char **argv)
{
	int	fd;
	int	len;

	check(argc != 2, 1, ERR_PARSER_ARGC);
	fd = open(argv[argc - 1], O_RDONLY);
	check(fd < 0, 1, ERR_PARSER_OPEN);
	len = read(fd, 0, 0);
	check(len < 0, 1, ERR_PARSER_READ);
	return (fd);
}

t_level *parse(int fd)
{
	char	*line;
	t_level	*root;
	t_level	*parent;
	t_level	*child;
	int		gnl_status;

	root = level_new();
	root->type = LTYPE_NODE;
	root->offset = -2;
	root->child_offset = -2;
	root->data = ptr_array_new(10);
	parent = root;
	while (1)
	{
		gnl_status = get_next_line(fd, &line);
		check(gnl_status == -1, 1, ERR_PARSER_GNL);
		if (gnl_status == 0)
			break;
		
		child = level_from_line(line);
		if (!child)
		{
			free(line);
			continue;
		}

		while (parent->parent && child->offset <= parent->child_offset)
			parent = parent->parent;
		if (parent->data->used == 0)
			parent->child_offset = child->offset;
		else
			check(parent->child_offset != child->offset, 1, ERR_PARSER_INVALID_OFFSET);
		ptr_array_add(parent->data, child);
		child->parent = parent;
		if (child->type == LTYPE_NODE)
			parent = child;
		
		free(line);
	}
	ft_putendl(line);
	free(line);
	return (root);
}

void parser(t_rtv *rtv, int argc, char **argv)
{
	int		fd;
	t_level	*root;

	fd = check_arguments(argc, argv);
	root = parse(fd);
	validate(rtv, root);
}
