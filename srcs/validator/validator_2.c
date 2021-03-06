/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:31:14 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:35:53 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	color = (t_color){0, 0, 0};
	i = 0;
	while (i < root->data->used)
	{
		level = root->data->data[i];
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "red"))
			color.red = validate_color_component(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "green"))
			color.green = validate_color_component(level->value);
		if (level->type == LTYPE_LEAF && !ft_strcmp(level->key, "blue"))
			color.blue = validate_color_component(level->value);
		i++;
	}
	return (color);
}

/**
 *	Функция для валидации радиуса
 *	@returns Квадрат радиуса
 */
double	validate_radius(t_level *root)
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
double	validate_specular(t_level *root)
{
	int	specular;

	specular = -1;
	if (root->type == LTYPE_LEAF && !ft_strcmp(root->key, "specular"))
		specular = ft_atoi(root->value);
	return (specular);
}

/**
 *	Функция для валидации коэффициента отражения
 */
double	validate_reflection(t_level *root)
{
	int	reflection;

	reflection = 0;
	if (root->type == LTYPE_LEAF && !ft_strcmp(root->key, "reflection"))
		reflection = ft_atoi(root->value);
	if (reflection < 0)
		reflection = 0;
	else if (reflection > 100)
		reflection = 100;
	return (reflection / 100.0);
}
