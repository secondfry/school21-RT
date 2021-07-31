#include "parser.h"

static void	recurse_parse(
	int fd,
	char **memory,
	const char *line,
	t_level *child
)
{
	t_level	*inner_child;

	*memory = ft_strdup(line);
	(*memory)[child->offset] = ' ';
	inner_child = parse(fd, memory);
	child->child_offset = inner_child->offset;
	inner_child->parent = child;
	ptr_array_add(child->data, inner_child);
}

static void	local_get_next_line(int fd, char **memory, char **line)
{
	char	gnl_status;

	if (*memory)
	{
		*line = *memory;
		*memory = (void *)0;
		return ;
	}
	gnl_status = get_next_line(fd, line);
	check(gnl_status == -1, 1, ERR_PARSER_GNL);
	if (gnl_status == 0)
	{
		free(*line);
		*line = (void *)0;
		return ;
	}
}

static void	process_type(
	t_level **parent,
	t_level *child,
	t_process_type_args args
)
{
	if (child->type == LTYPE_NODE)
		*parent = child;
	if (child->type == LTYPE_LIST_NODE)
		recurse_parse(args.fd, args.memory, args.line, child);
}

static _Bool	process_offset(t_level *root, char *line, char **memory)
{
	t_byte	offset;

	offset = get_offset(line);
	if (offset < root->offset)
	{
		*memory = line;
		return (1);
	}
	return (0);
}

t_level	*parse(int fd, char **memory)
{
	char	*line;
	t_level	*root;
	t_level	*parent;
	t_level	*child;

	init_root(&root, memory);
	parent = root;
	line = 0;
	while (1)
	{
		free(line);
		local_get_next_line(fd, memory, &line);
		if (line == 0)
			break ;
		if (process_offset(root, line, memory))
			return (root);
		child = level_from_line(line);
		if (!child)
			continue ;
		process_parent_child(&parent, child);
		process_type(&parent, child, (t_process_type_args){fd, memory, line});
	}
	return (root);
}
