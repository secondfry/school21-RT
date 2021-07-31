#include "parser.h"

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

void	init_root(t_level **root, char **memory)
{
	t_level	*ret;

	ret = level_new();
	ret->type = LTYPE_NODE;
	ret->offset = get_offset(*memory);
	ret->child_offset = -2;
	ret->data = ptr_array_new(10);
	*root = ret;
}

static void	find_proper_parent(t_level **parent_ptr, t_level *child)
{
	t_level	*parent;

	parent = *parent_ptr;
	while (
		parent->parent
		&& (
			child->offset < parent->child_offset
			|| (parent->child_offset == -1 && child->offset <= parent->offset)
		)
	)
		parent = parent->parent;
	*parent_ptr = parent;
}

static void	check_child_offset(t_level *parent, t_level *child)
{
	if (parent->data->used == 0)
		parent->child_offset = child->offset;
	else
		check(\
			parent->child_offset != child->offset, \
			1, \
			ERR_PARSER_INVALID_OFFSET \
		);
}

void	process_parent_child(t_level **parent, t_level *child)
{
	find_proper_parent(parent, child);
	check_child_offset(*parent, child);
	ptr_array_add((*parent)->data, child);
	child->parent = *parent;
}
