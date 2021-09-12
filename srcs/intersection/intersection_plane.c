/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:33:52 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:33:54 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection_plane.h"
#include "intersection_common.h"

// https://www.scratchapixel.com/
// lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/
// ray-plane-and-ray-disk-intersection

// (C - P) dot N = 0
// O + D * t = P

// (C - (O + D * t)) dot N = 0
// (C - O - D * t) dot N = 0
// (C - O) dot N - t * D dot N = 0
// t = (C - O) dot N / D dot N

static double	intersection_plane(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx
)
{
	const t_vector_4	vec_c = rtv->planes[idx].position;
	const t_vector_4	vec_co = vector_sub(vec_c, params->vec_o);
	const double		a = vector_dot(rtv->planes[idx].normal, vec_co);
	const double		b = vector_dot(rtv->planes[idx].normal, params->vec_d);

	if (b < EPSILON && b > -1 * EPSILON)
	{
		return (1.0 / 0.0);
	}
	return (a / b);
}

t_intersection	intersection_plane_closest(
	t_rtv *rtv,
	t_intersect_params *params
)
{
	double	t_closest;
	t_byte	idx;
	t_byte	i;
	double	t;

	t_closest = 1.0 / 0.0;
	idx = -1;
	i = 0;
	while (i < MAX_PLANES)
	{
		if (!(rtv->planes[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		t = intersection_plane(rtv, params, i);
		check_cropping_plane(rtv, params->vec_o, params->vec_d, &t);
		if (t > params->t_min && t < params->t_max && t < t_closest)
		{
			t_closest = t;
			idx = i;
		}
		i++;
	}
	return ((t_intersection){t_closest, idx, IPLANE});
}
