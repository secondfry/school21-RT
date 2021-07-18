#include "parser.h"

static t_byte	validate_light_point_one_position(
	t_rtv *rtv,
	t_level *root,
	t_byte idx
)
{
	const t_vector_4	position = get_vector(root);

	vector_set(&rtv->plights[idx].position, &position);
	return (1);
}

static t_byte	validate_light_point_one_intensity(
	t_rtv *rtv,
	t_level *root,
	t_byte idx
)
{
	rtv->plights[idx].intensity = (float) ft_atoi(root->value) / 100.f;
	return (1);
}

static t_byte	validate_light_point_one(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	root = root->data->data[0];
	check(root->type != LTYPE_NODE, 1, ERR_VALIDATOR_LIGHT_POINT_INVALID);
	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "position"))
			res += validate_light_point_one_position(rtv, level, idx);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "intensity"))
			res += validate_light_point_one_intensity(rtv, level, idx);
		i++;
	}
	check(res != 2, 1, ERR_VALIDATOR_LIGHT_POINT_INVALID);
	rtv->plights[idx].traits = TRAIT_EXISTS;
	return (1);
}

t_byte	validate_light_point(t_rtv *rtv, t_level *root)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		check(level->type != LTYPE_LIST_NODE, \
			1, ERR_VALIDATOR_LIGHT_POINT_LIST);
		res += validate_light_point_one(rtv, level, i);
		i++;
	}
	if (res == 0)
		ft_putendl("[validator] Scene has no point lights");
	return (1);
}
