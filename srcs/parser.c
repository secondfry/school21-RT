#include "parser.h"

t_level *level_new()
{
	t_level *ret;

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

t_byte validate_light_ambient(t_rtv *rtv, t_level *root)
{
	rtv->ambient = (float) ft_atoi(root->value) / 100.f;
	return (1);
}

t_vector_4 get_vector(t_level *root)
{
	float coord[3];

	coord[0] = 0;
	coord[1] = 0;
	coord[2] = 0;
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "x"))
			coord[0] = ft_atoi(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "y"))
			coord[1] = ft_atoi(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "z"))
			coord[2] = ft_atoi(level->value);
	}
	return ((t_vector_4) { coord[0], coord[1], coord[2], 1.f });
}

t_byte validate_light_point_one_position(t_rtv *rtv, t_level *root, t_byte idx)
{
	const t_vector_4 position = get_vector(root);

	ft_memcpy((void *)&rtv->plights[idx].position, (void *)&position, sizeof(t_vector_4));
	return (1);
}

t_byte validate_light_point_one_intensity(t_rtv *rtv, t_level *root, t_byte idx)
{
	rtv->plights[idx].intensity = (float) ft_atoi(root->value) / 100.f;
	return (1);
}

t_byte validate_light_point_one(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte res;

	root = root->data->data[0];
	check(root->type != LTYPE_NODE, 1, ERR_VALIDATOR_LIGHT_POINT_INVALID);
	res = 0;
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "position"))
			res += validate_light_point_one_position(rtv, level, idx);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "intensity"))
			res += validate_light_point_one_intensity(rtv, level, idx);
	}
	check(res != 2, 1, ERR_VALIDATOR_LIGHT_POINT_INVALID);
	rtv->plights[idx].traits = TRAIT_EXISTS;
	return (1);
}

t_byte validate_light_point(t_rtv *rtv, t_level *root)
{
	t_byte res;

	res = 0;
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		check(level->type != LTYPE_LIST_NODE, 1, ERR_VALIDATOR_LIGHT_POINT_LIST);
		res += validate_light_point_one(rtv, level, i);
	}
	if (res == 0)
		ft_putendl("[validator] Scene has no point lights");
	return (1);
}

t_byte validate_light_directional_one_directional(t_rtv *rtv, t_level *root, t_byte idx)
{
	const t_vector_4 direction = get_vector(root);
	const float w = 0.f;

	ft_memcpy((void *)&direction.w, (void *)&w, sizeof(float));
	ft_memcpy((void *)&rtv->dlights[idx].direction, (void *)&direction, sizeof(t_vector_4));
	return (1);
}

t_byte validate_light_directional_one_intensity(t_rtv *rtv, t_level *root, t_byte idx)
{
	rtv->dlights[idx].intensity = (float) ft_atoi(root->value) / 100.f;
	return (1);
}

t_byte validate_light_directional_one(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte res;

	root = root->data->data[0];
	check(root->type != LTYPE_NODE, 1, ERR_VALIDATOR_LIGHT_DIRECTIONAL_INVALID);
	res = 0;
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "direction"))
			res += validate_light_directional_one_directional(rtv, level, idx);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "intensity"))
			res += validate_light_directional_one_intensity(rtv, level, idx);
	}
	check(res != 2, 1, ERR_VALIDATOR_LIGHT_DIRECTIONAL_INVALID);
	rtv->dlights[idx].traits = TRAIT_EXISTS;
	return (1);
}

t_byte validate_light_directional(t_rtv *rtv, t_level *root)
{
	t_byte res;

	res = 0;
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		check(level->type != LTYPE_LIST_NODE, 1, ERR_VALIDATOR_LIGHT_DIRECTIONAL_LIST);
		res += validate_light_directional_one(rtv, level, i);
	}
	if (res == 0)
		ft_putendl("[validator] Scene has no directional lights");
	return (1);
}

t_byte validate_light(t_rtv *rtv, t_level *root)
{
	t_byte res;

	res = 0;
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "ambient"))
			res += validate_light_ambient(rtv, level);
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "point"))
			res += validate_light_point(rtv, level);
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "directional"))
			res += validate_light_directional(rtv, level);
	}
	check(res != 3, 1, ERR_VALIDATOR_LIGHT_INCOMPLETE);
	return (1);
}

//	TODO: дописать валидатор
void validate(t_rtv *rtv, t_level *root)
{
	for (t_byte i = 0; i < root->data->used; i++)
	{
		t_level *level = root->data->data[i];
		check(level->type != LTYPE_NODE, 1, ERR_VALIDATOR_ROOT_NODES);
		if (!ft_strcmp(level->key, "light"))
			validate_light(rtv, level);
		// Добавить валидацию сферы, конуса, цилиндра, плоскости
	}
}

t_level *level_from_line(const char *line)
{
	t_level *ret;

	t_byte i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 0)
		return (0);
	t_byte offset = i;

	check(line[i] == '-' && line[i + 1] == 0, 1, ERR_PARSER_OADYAML_LIST_NAN);

	if (line[i] == '-' && line[i + 1] == ' ')
	{
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
			t_byte q = ft_strlen(line) - 1;
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

		return ret;
	}

	while (line[i] && line[i] != ':')
		i++;
	check(line[i] == 0, 1, ERR_PARSER_NO_COLON);
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
	int fd;
	int len;

	check(argc != 2, 1, ERR_PARSER_ARGC);
	fd = open(argv[argc - 1], O_RDONLY);
	check(fd < 0, 1, ERR_PARSER_OPEN);
	len = read(fd, 0, 0);
	check(len < 0, 1, ERR_PARSER_READ);
	return (fd);
}

short get_offset(char *line)
{
	short i;

	if (!line)
		return (-2);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

t_level *parse(int fd, char **memory)
{
	char *line;
	t_level *root;
	t_level *parent;
	t_level *child;
	int gnl_status;

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
				break;
		}

		short offset = get_offset(line);
		if (offset < root->offset)
		{
			*memory = line;
			return (root);
		}

		child = level_from_line(line);
		if (!child)
		{
			free(line);
			continue;
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
		{
			*memory = ft_strdup(line);
			(*memory)[child->offset] = ' ';
			t_level *inner_child = parse(fd, memory);
			child->child_offset = inner_child->offset;
			inner_child->parent = child;
			ptr_array_add(child->data, inner_child);
		}

		free(line);
	}
	free(line);
	return (root);
}

void parser(t_rtv *rtv, int argc, char **argv)
{
	int fd;
	t_level *root;
	char *memory;

	fd = check_arguments(argc, argv);
	memory = 0;
	root = parse(fd, &memory);
	validate(rtv, root);
}
