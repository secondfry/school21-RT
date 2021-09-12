/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:33:58 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:34:00 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection_sphere.h"

// https://www.gabrielgambetta.com/
// computer-graphics-from-scratch/04-shadows-and-reflections.html

static void	intersection_sphere(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx,
	double t[2]
)
{
	const t_intersection_sphere	data = {
		rtv->spheres[idx].vectors[VCTR_SPHERE_C],
		vector_sub(params->vec_o, data.vec_c),
		vector_dot(params->vec_d, params->vec_d),
		2 * vector_dot(params->vec_d, data.vec_co),
		vector_dot(data.vec_co, data.vec_co) - rtv->spheres[idx].radius_squared,
		data.b * data.b - 4 * data.a * data.c,
		sqrt(data.cubed)
	};

	if (data.cubed < 0)
	{
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return ;
	}
	t[0] = (-1 * data.b + data.sqrt) / (2 * data.a);
	t[1] = (-1 * data.b - data.sqrt) / (2 * data.a);
}

t_intersection	intersection_sphere_closest(
	t_rtv *rtv,
	t_intersect_params *params
)
{
	t_intersection	ret;
	t_byte			i;
	double			t[2];

	ret.distance = 1.0 / 0.0;
	ret.idx = -1;
	ret.type = ISPHERE;
	i = 0;
	while (i < MAX_SPHERES)
	{
		if (!(rtv->spheres[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		intersection_sphere(rtv, params, i, t);
		check_cropping_plane(rtv, params->vec_o, params->vec_d, t + 0);
		check_intersection(&ret, params, t[0], i);
		check_cropping_plane(rtv, params->vec_o, params->vec_d, t + 1);
		check_intersection(&ret, params, t[1], i);
		i++;
	}
	return (ret);
}
