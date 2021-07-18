#include "parser.h"

static t_byte	try_process_position(t_rtv *rtv, t_byte idx, t_level *level)
{
	const t_vector_4	vector = vector_new(0, 0, 0, 0);

	if (level->type != LTYPE_NODE || ft_strcmp(level->key, "position"))
		return (0);
	validate_vector(&vector, level);
	vector_set(&rtv->spheres[idx].vectors[VCTR_SPHERE_C], &vector);
	return (1);
}

static t_byte	try_process_color(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_NODE || ft_strcmp(level->key, "color"))
		return (0);
	rtv->spheres[idx].color = validate_color(level);
	return (1);
}

static t_byte	try_process_radius(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "radius"))
		return (0);
	rtv->spheres[idx].radius_squared = validate_radius(level);
	return (1);
}

static t_byte	try_process_specular(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "specular"))
		return (0);
	rtv->spheres[idx].specular = validate_specular(level);
	return (1);
}

/**
 *	Функция для валидации параметров сферы
 */
t_byte	validate_sphere(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte		res;
	t_byte		i;
	t_level		*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		res += try_process_position(rtv, idx, level);
		res += try_process_color(rtv, idx, level);
		res += try_process_radius(rtv, idx, level);
		res += try_process_specular(rtv, idx, level);
		i++;
	}
	check(res != 4, 1, "[ERR] SPHERE IS INVALID\n");
	rtv->spheres[idx].traits = TRAIT_EXISTS;
	return (1);
}
