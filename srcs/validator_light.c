#include "parser.h"

static t_byte	validate_light_ambient(t_rtv *rtv, t_level *root)
{
	rtv->ambient = (float) ft_atoi(root->value) / 100.f;
	return (1);
}

t_byte	validate_light(t_rtv *rtv, t_level *root)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "ambient"))
			res += validate_light_ambient(rtv, level);
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "point"))
			res += validate_light_point(rtv, level);
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "directional"))
			res += validate_light_directional(rtv, level);
		i++;
	}
	check(res != 3, 1, ERR_VALIDATOR_LIGHT_INCOMPLETE);
	return (1);
}
