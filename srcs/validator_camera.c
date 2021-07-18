#include "parser.h"

t_byte	validate_camera(t_rtv *rtv, t_level *root)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "position"))
		{
			vector_set_by_value(&rtv->camera_position, get_vector(level));
			res++;
		}
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "rotation"))
		{
			vector_set_by_value(&rtv->camera_angles, get_vector(level));
			res++;
		}
		i++;
	}
	check(res != 2, 1, ERR_VALIDATOR_LIGHT_INCOMPLETE);
	return (1);
}
