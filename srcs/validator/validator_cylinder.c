#include "parser.h"

static t_byte	try_process_vector(
	t_cylinder *cylinder,
	t_level *level,
	char *key,
	t_byte idx
)
{
	const t_vector_4	vector = vector_new(0, 0, 0, 0);

	if (level->type != LTYPE_NODE || ft_strcmp(level->key, key))
		return (0);
	validate_vector(&vector, level);
	vector_set(&cylinder->vectors[idx], &vector);
	return (1);
}

static t_byte	try_process_radius(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "radius"))
		return (0);
	rtv->cylinders[idx].radius2 = validate_radius(level);
	return (1);
}

static t_byte	try_process_color(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_NODE || ft_strcmp(level->key, "color"))
		return (0);
	rtv->cylinders[idx].color = validate_color(level);
	return (1);
}

static t_byte	try_process_specular(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "specular"))
		return (0);
	rtv->cylinders[idx].specular = validate_specular(level);
	return (1);
}

/**
 *	Функция для валидации параметров цилиндра
 */
t_byte	validate_cylinder(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte				res;
	t_byte				i;
	t_level				*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		res += try_process_vector(&rtv->cylinders[idx], level, \
			"position", VCTR_CYLINDER_C0);
		res += try_process_vector(&rtv->cylinders[idx], level, \
			"direction", VCTR_CYLINDER_C1);
		res += try_process_radius(rtv, idx, level);
		res += try_process_color(rtv, idx, level);
		res += try_process_specular(rtv, idx, level);
		i++;
	}
	vector_set_by_value(&rtv->cylinders[idx].vectors[VCTR_CYLINDER_C0C1], \
		vector_normalize(vector_sub(\
		rtv->cylinders[idx].vectors[VCTR_CYLINDER_C1], \
		rtv->cylinders[idx].vectors[VCTR_CYLINDER_C0])));
	check(res != 5, 1, "[ERR] CYLINDER IS INVALID\n");
	rtv->cylinders[idx].traits = TRAIT_EXISTS;
	return (1);
}
