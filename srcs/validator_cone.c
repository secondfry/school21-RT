#include "parser.h"

static t_byte	try_process_vector(
	t_cone *cone,
	t_level *level,
	char *key,
	t_byte idx
)
{
	const t_vector_4	vector = vector_new(0, 0, 0, 0);

	if (level->type != LTYPE_NODE || ft_strcmp(level->key, key))
		return (0);
	validate_vector(&vector, level);
	vector_set(&cone->vectors[idx], &vector);
	return (1);
}

static t_byte	try_process_angle(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "angle"))
		return (0);
	rtv->cones[idx].angle = validate_angle(level);
	rtv->cones[idx].cos = cosf(rtv->cones[idx].angle);
	rtv->cones[idx].cos2 = rtv->cones[idx].cos * rtv->cones[idx].cos;
	return (1);
}

static t_byte	try_process_color(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_NODE || ft_strcmp(level->key, "color"))
		return (0);
	rtv->cones[idx].color = validate_color(level);
	return (1);
}

static t_byte	try_process_specular(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "specular"))
		return (0);
	rtv->cones[idx].specular = validate_specular(level);
	return (1);
}

/**
 *	Функция для валидации параметров конуса
 */
t_byte	validate_cone(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		res += try_process_vector(&rtv->cones[idx], level, "position", 0);
		res += try_process_vector(&rtv->cones[idx], level, "direction", 1);
		res += try_process_angle(rtv, idx, level);
		res += try_process_color(rtv, idx, level);
		res += try_process_specular(rtv, idx, level);
		i++;
	}
	vector_set_by_value(&rtv->cones[idx].vectors[VCTR_CONE_C0C1], \
		vector_normalize(vector_sub(rtv->cones[idx].vectors[VCTR_CONE_C1], \
		rtv->cones[idx].vectors[VCTR_CONE_C0])));
	check(res != 5, 1, "[ERR] CONE IS INVALID\n");
	rtv->cones[idx].traits = TRAIT_EXISTS;
	return (1);
}
