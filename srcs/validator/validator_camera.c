/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:36:16 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:36:20 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	check(res != 2, 1, ERR_VALIDATOR_CAMERA_INCOMPLETE);
	return (1);
}
