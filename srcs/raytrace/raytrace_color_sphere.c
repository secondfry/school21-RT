/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_color_sphere.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:24:25 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 20:28:31 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace/raytrace_color_sphere.h"
#include "defines.h"
#include "rtv.h"
#include "vector.h"

static void	_get_uv_sphere(
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

static void	_check_texture_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	double uv[2]
)
{
	const unsigned int	u = uv[0] * rtv->textures[1].width;
	const unsigned int	v = uv[1] * rtv->textures[1].height;
	const size_t		offset = 4 * (v * rtv->textures[1].width + u);
	const t_color		color = {
		rtv->textures[1].data[offset + 0],
		rtv->textures[1].data[offset + 1],
		rtv->textures[1].data[offset + 2],
	};

	if (rtv->textures[1].data[offset + 3] == 0)
		return ;
	ft_memcpy((void *)&params->color, &color, sizeof(t_color));
}

void	check_texture_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr
)
{
	double	uv[2];

	if (intr->idx > MAX_SPHERES - 1)
		return ;
	if (!(rtv->spheres[intr->idx].traits & TRAIT_TEXTURED))
		return ;
	if (!rtv->textures[1].data)
		return ;
	_get_uv_sphere(rtv, params, intr, uv);
	return (_check_texture_sphere(rtv, params, uv));
}
