/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:33:18 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:33:21 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection_cone.h"

// https://lousodrome.net/
// blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

static void	intersection_cone(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx,
	double t[2]
)
{
	const t_intersection_cone	data = {
		rtv->cones[idx].vectors[VCTR_CONE_C0],
		vector_sub(params->vec_o, data.vec_c),
		rtv->cones[idx].vectors[VCTR_CONE_C0C1],
		vector_dot(params->vec_d, data.vec_cq),
		vector_dot(data.vec_co, data.vec_cq),
		vector_dot(params->vec_d, data.vec_co),
		vector_dot(data.vec_co, data.vec_co),
		rtv->cones[idx].cos2,
		data.d_dot_cq * data.d_dot_cq - data.cos2,
		2 * (data.d_dot_cq * data.co_dot_cq - data.d_dot_co * data.cos2),
		data.co_dot_cq * data.co_dot_cq - data.co_dot_co * data.cos2,
		(data.b * data.b) - (4.0 * data.a * data.c),
		sqrt(data.cubed)
	};

	if (data.cubed < 0)
	{
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return ;
	}
	t[0] = (-1 * data.b - data.sqrt) / (2.0 * data.a);
	t[1] = (-1 * data.b + data.sqrt) / (2.0 * data.a);
}

t_intersection	intersection_cone_closest(
	t_rtv *rtv,
	t_intersect_params *params
)
{
	t_intersection	ret;
	t_byte			i;
	double			t[2];

	ret.distance = 1.0 / 0.0;
	ret.idx = -1;
	ret.type = ICONE;
	i = 0;
	while (i < MAX_CONES)
	{
		if (!(rtv->cones[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		intersection_cone(rtv, params, i, t);
		check_cropping_plane(rtv, params->vec_o, params->vec_d, t + 0);
		check_intersection(&ret, params, t[0], i);
		check_cropping_plane(rtv, params->vec_o, params->vec_d, t + 1);
		check_intersection(&ret, params, t[1], i);
		i++;
	}
	return (ret);
}
