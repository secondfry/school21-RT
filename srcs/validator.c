/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:45:52 by pcarolei          #+#    #+#             */
/*   Updated: 2021/07/18 19:25:45 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_vector_4	get_vector(t_level *root)
{
	float	coord[3];
	t_byte	i;
	t_level	*level;

	coord[0] = 0;
	coord[1] = 0;
	coord[2] = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "x"))
			coord[0] = ft_atoi(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "y"))
			coord[1] = ft_atoi(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "z"))
			coord[2] = ft_atoi(level->value);
		i++;
	}
	return ((t_vector_4){coord[0], coord[1], coord[2], 1.f});
}

/**
 *	Функция для валидации угла
 */
//	TODO: объединить в функцию валидации скаляра вместе с specular
float	validate_angle(t_level *root)
{
	float	angle;

	angle = -1;
	if (root->type == LTYPE_LEAF && !ft_strcmp(root->key, "angle"))
		angle = (float)ft_atoi(root->value) * M_PI_F / 180.f;
	return (angle);
}

void	validate(t_rtv *rtv, t_level *root)
{
	t_byte	i;
	t_level	*level;

	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		check(level->type != LTYPE_NODE, 1, ERR_VALIDATOR_ROOT_NODES);
		if (!ft_strcmp(level->key, "light"))
			validate_light(rtv, level);
		if (!ft_strcmp(level->key, "sphere"))
			validate_object(rtv, level, ISPHERE);
		if (!ft_strcmp(level->key, "plane"))
			validate_object(rtv, level, IPLANE);
		if (!ft_strcmp(level->key, "cylinder"))
			validate_object(rtv, level, ICYLINDER);
		if (!ft_strcmp(level->key, "cone"))
			validate_object(rtv, level, ICONE);
		i++;
	}
}

/**
 *	Функция для валидации списка объектов
 *	(света/сфер/плоскостей/конусов/цилиндров)
 */
t_byte	validate_object(t_rtv *rtv, t_level *root, t_byte obj_type)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	res = 0;
	check(root->type != LTYPE_NODE, 1, "[ERR] EXPECTED NODE\n");
	check(!root->data || !root->data->used, \
		1, "[ERR] EXPECTED ONE OR MORE OBJECTS\n");
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (obj_type == ISPHERE)
			validate_sphere(rtv, level->data->data[0], i);
		if (obj_type == IPLANE)
			validate_plane(rtv, level->data->data[0], i);
		if (obj_type == ICYLINDER)
			validate_cylinder(rtv, level->data->data[0], i);
		if (obj_type == ICONE)
			validate_cone(rtv, level->data->data[0], i);
		i++;
	}
	return (1);
}

/**
 *	Функция для валидации параметров сферы
 */
t_byte	validate_sphere(t_rtv *rtv, t_level *root, t_byte idx)
{
	t_byte		res;
	t_vector_4	*dest;
	t_byte		i;
	t_level		*level;

	res = 0;
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "position"))
		{
			dest = &rtv->spheres[idx].vectors[VCTR_SPHERE_C];
			res += validate_vector(dest, level);
		}
		if (level->type == LTYPE_NODE && !ft_strcmp(level->key, "color"))
		{
			rtv->spheres[idx].color = validate_color(level);
			res++;
		}
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "radius"))
		{
			rtv->spheres[idx].radius_squared = validate_radius(level);
			res++;
		}
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "specular"))
		{
			rtv->spheres[idx].specular = validate_specular(level);
			res++;
		}
		i++;
	}
	check(res != 4, 1, "[ERR] SPHERE IS INVALID\n");
	rtv->spheres[idx].traits = TRAIT_EXISTS;
	return (1);
}

/**
 *	Функция для валидации вектора
 */
t_byte	validate_vector(t_vector_4 *dest, t_level *root)
{
	t_byte	res;
	t_byte	i;
	t_level	*level;

	res = 0;
	check(root->data->used != 3, \
		1, "[ERR] VECTOR HAVE WRONG AMOUNT OF PARAMETERS\n");
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "x"))
			res++;
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "y"))
			res++;
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "z"))
			res++;
		i++;
	}
	check(res != 3, 1, "[ERR] VECTOR PARAMETERS ERROR\n");
	vector_set_by_value(dest, get_vector(root));
	return (1);
}

/**
 *	Функция для валидации компонента цвета
 *	(представленного целым числом от нуля до 255)
 */
static t_byte	validate_color_component(char *value)
{
	t_byte	component;

	component = ft_atoi(value);
	return (component);
}

/**
 *	Функция для валидации цвета
 */
t_color	validate_color(t_level *root)
{
	t_color	color;
	t_byte	i;
	t_level	*level;

	check(root->data->used != 3, \
		1, "[ERR] COLOR HAVE WRONG AMOUNT OF PARAMETERS\n");
	color = color_new(0, 0, 0);
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "red"))
			color[TCRED] = validate_color_component(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "green"))
			color[TCGREEN] = validate_color_component(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "blue"))
			color[TCBLUE] = validate_color_component(level->value);
		i++;
	}
	return (color);
}

/**
 *	Функция для валидации радиуса
 *	@returns Квадрат радиуса
 */
float	validate_radius(t_level *root)
{
	int	radius;

	radius = -1;
	if (root->type == LTYPE_LEAF && !ft_strcmp(root->key, "radius"))
	{
		radius = ft_atoi(root->value);
	}
	check(radius < 0, 1, "[ERR] INVALID RADIUS INPUT\n");
	return (radius * radius);
}

/**
 *	Функция для валидации зеркальности
 */
float	validate_specular(t_level *root)
{
	int	specular;

	specular = -1;
	if (root->type == LTYPE_LEAF && !ft_strcmp(root->key, "specular"))
		specular = ft_atoi(root->value);
	return (specular);
}
