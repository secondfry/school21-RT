/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_common.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:33:06 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:33:09 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection_common.h"
#include "vector.h"

static void	_check_cropping_plane(
	t_rtv *rtv,
	t_vector_4 vec_o,
	t_vector_4 vec_d,
	double *distance
)
{
	const t_vector_4	vec_p = vector_add(vec_o, \
		vector_mult(vec_d, *distance));
	const t_vector_4	vec_pq = vector_sub(vec_p, rtv->slice.position);
	const bool			ok = vector_dot(vec_pq, rtv->slice.normal) > 0;

	if (!ok)
		*distance = 1.0 / 0.0;
}

void	check_cropping_plane(
	t_rtv *rtv,
	t_vector_4 vec_o,
	t_vector_4 vec_d,
	double *distance
)
{
	if (!(rtv->slice.traits & TRAIT_EXISTS))
		return ;
	return (_check_cropping_plane(rtv, vec_o, vec_d, distance));
}

void	check_intersection(
	t_intersection *ret,
	t_intersect_params *params,
	double t,
	t_byte i
)
{
	if (t > params->t_min && t < params->t_max && t < ret->distance)
	{
		ret->distance = t;
		ret->idx = i;
	}
}
