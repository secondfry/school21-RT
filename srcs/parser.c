#include "parser.h"

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

static void	free_parsed_struct(t_level *root)
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
