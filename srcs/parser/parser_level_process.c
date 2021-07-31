#include "parser.h"

static void	fill_level_leaf(
	t_level *level,
	t_byte type,
	const char *line,
	t_byte offset
)
{
	t_byte	i;

	i = ft_strlen(line) - 1;
	while (line[i] == ' ')
		i--;
	i++;
	level->value = ft_strsub(line, offset, i - offset);
	level->type = type;
}

static void	fill_level_node(t_level *level, t_byte type)
{
	level->data = ptr_array_new(10);
	level->type = type;
}

static t_level	*level_from_line_list(const char *line, t_byte i)
{
	t_level	*ret;
	t_byte	offset;

	offset = i;
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
		fill_level_leaf(ret, LTYPE_LIST_LEAF, line, offset);
	else
		fill_level_node(ret, LTYPE_LIST_NODE);
	return (ret);
}

static void	set_key_trimmed(
	t_level *level,
	const char *line,
	t_byte start,
	t_byte finish
)
{
	t_byte	i;
	t_byte	len;

	i = finish - 1;
	while (line[i] == ' ')
		i--;
	i++;
	len = i - start;
	level->key = ft_strsub(line, start, len);
}

t_level	*level_from_line(const char *line)
{
	t_level	*ret;
	t_byte	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 0 || line[i] == '#')
		return (0);
	check(line[i] == '-' && line[i + 1] == 0, 1, ERR_PARSER_OADYAML_LIST_NAN);
	if (line[i] == '-' && line[i + 1] == ' ')
		return (level_from_line_list(line, i));
	ret = level_new();
	ret->offset = i;
	while (line[i] && line[i] != ':')
		i++;
	check(line[i] == 0, 1, ERR_PARSER_NO_COLON);
	set_key_trimmed(ret, line, ret->offset, i);
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 0)
		fill_level_node(ret, LTYPE_NODE);
	else
		fill_level_leaf(ret, LTYPE_LEAF, line, i);
	return (ret);
}
