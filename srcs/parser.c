#include "parser.h"

t_level	*level_new(void)
{
	t_level	*ret;

	ret = (t_level *)malloc(sizeof(t_level));
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret->key = (void *)0;
	ret->type = LTYPE_UNSET;
	ret->parent = (void *)0;
	ret->value = (void *)0;
	ret->data = (void *)0;
	ret->offset = -1;
	ret->child_offset = -1;
	return (ret);
}

t_vector_4	get_vector(t_level *root)
{
	float	coord[3];
	t_byte	i;
	t_level	*level;

	coord[0] = 0;
	coord[1] = 0;
	coord[2] = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "x"))
			coord[0] = ft_atoi(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "y"))
			coord[1] = ft_atoi(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "z"))
			coord[2] = ft_atoi(level->value);
		i++;
	}
	return ((t_vector_4){coord[0], coord[1], coord[2], 1.f});
}

t_level	*level_from_line_list(const char *line, t_byte offset, t_byte i)
{
	t_level	*ret;
	t_byte	q;

	ret = level_new();
	ret->offset = offset;
	i += 2;
	while (line[i] && line[i] == ' ')
		i++;
	check(line[i] == 0, 1, ERR_PARSER_OADYAML_LIST_NAN);
	offset = i;
	while (line[i] && line[i] != ':')
		i++;
	if (line[i] == 0)
	{
		q = ft_strlen(line) - 1;
		while (line[q] == ' ')
			q--;
		q++;
		ret->value = ft_strsub(line, offset, q - offset);
		ret->type = LTYPE_LIST_LEAF;
	}
	else
	{
		ret->data = ptr_array_new(10);
		ret->type = LTYPE_LIST_NODE;
	}
	return (ret);
}

t_level	*level_from_line(const char *line)
{
	t_level	*ret;
	t_byte	i;
	t_byte	q;
	t_byte	offset;
	t_byte	key_len;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 0)
		return (0);
	offset = i;
	check(line[i] == '-' && line[i + 1] == 0, 1, ERR_PARSER_OADYAML_LIST_NAN);
	if (line[i] == '-' && line[i + 1] == ' ')
		return (level_from_line_list(line, offset, i));
	ret = level_new();
	ret->offset = offset;
	while (line[i] && line[i] != ':')
		i++;
	check(line[i] == 0, 1, ERR_PARSER_NO_COLON);
	q = i - 1;
	while (line[q] == ' ')
		q--;
	q++;
	key_len = q - offset;
	ret->key = ft_strsub(line, offset, key_len);
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 0)
	{
		ret->type = LTYPE_NODE;
		ret->data = ptr_array_new(10);
	}
	else
	{
		ret->type = LTYPE_LEAF;
		q = ft_strlen(line) - 1;
		while (line[q] == ' ')
			q--;
		q++;
		ret->value = ft_strsub(line, i, q - i);
	}
	return (ret);
}

int	check_arguments(int argc, char **argv)
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

short	get_offset(char *line)
{
	short	i;

	if (!line)
		return (-2);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

void	recurse_parse(int fd, char **memory, const char *line, t_level *child)
{
	t_level	*inner_child;

	*memory = ft_strdup(line);
	(*memory)[child->offset] = ' ';
	inner_child = parse(fd, memory);
	child->child_offset = inner_child->offset;
	inner_child->parent = child;
	ptr_array_add(child->data, inner_child);
}

t_level	*parse(int fd, char **memory)
{
	int		gnl_status;
	char	*line;
	t_level	*root;
	t_level	*parent;
	t_level	*child;
	t_byte	offset;

	root = level_new();
	root->type = LTYPE_NODE;
	root->offset = get_offset(*memory);
	root->child_offset = -2;
	root->data = ptr_array_new(10);
	parent = root;
	while (1)
	{
		if (*memory)
		{
			line = *memory;
			*memory = (void *)0;
		}
		else
		{
			gnl_status = get_next_line(fd, &line);
			check(gnl_status == -1, 1, ERR_PARSER_GNL);
			if (gnl_status == 0)
				break ;
		}
		offset = get_offset(line);
		if (offset < root->offset)
		{
			*memory = line;
			return (root);
		}
		child = level_from_line(line);
		if (!child)
		{
			free(line);
			continue ;
		}
		while (
			parent->parent
			&& (
				child->offset < parent->child_offset
				|| (parent->child_offset == -1 && child->offset <= parent->offset)
			)
		)
			parent = parent->parent;
		if (parent->data->used == 0)
			parent->child_offset = child->offset;
		else
			check(parent->child_offset != child->offset, 1, ERR_PARSER_INVALID_OFFSET);
		ptr_array_add(parent->data, child);
		child->parent = parent;
		if (child->type == LTYPE_NODE)
			parent = child;
		if (child->type == LTYPE_LIST_NODE)
			recurse_parse(fd, memory, line, child);
		free(line);
	}
	free(line);
	return (root);
}

void	free_parsed_struct(t_level *root)
{
	size_t	i;

	if (root->type == LTYPE_LEAF || root->type == LTYPE_LIST_LEAF)
	{
		free(root->key);
		free(root->value);
		free(root);
		return ;
	}
	if (root->type == LTYPE_NODE || root->type == LTYPE_LIST_NODE)
	{
		free(root->key);
		i = 0;
		while (i < root->data->used)
		{
			free_parsed_struct(root->data->data[i]);
			i++;
		}
		ptr_array_destroy(root->data);
		free(root);
	}
}

void	parser(t_rtv *rtv, int argc, char **argv)
{
	int		fd;
	t_level	*root;
	char	*memory;

	fd = check_arguments(argc, argv);
	memory = 0;
	root = parse(fd, &memory);
	validate(rtv, root);
	free_parsed_struct(root);
	free(memory);
}
