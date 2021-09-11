/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_sphere_uv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:19:47 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 23:28:47 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace/raytrace_sphere_uv.h"
#include "rtv.h"
#include "vector.h"

void	get_uv_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr,
	double uv[2]
)
{
	const t_sphere		sphere = rtv->spheres[intr->idx];
	const t_vector_4	vec_pc = vector_normalize(
		vector_sub(sphere.vectors[VCTR_SPHERE_C], params->vec_p)
	);

	uv[0] = 0.5 - atan2(vec_pc.x, vec_pc.z) / M_PI / 2;
	uv[1] = 0.5 + asin(vec_pc.y) / M_PI;
}
