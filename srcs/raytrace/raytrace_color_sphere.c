/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_color_sphere.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:24:25 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 20:35:08 by oadhesiv         ###   ########.fr       */
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
	t_intersection *intr,
	double uv[2]
)
{
	const t_byte		texture_id = rtv->spheres[intr->idx].texture_id;
	const unsigned int	u = uv[0] * rtv->textures[texture_id].width;
	const unsigned int	v = uv[1] * rtv->textures[texture_id].height;
	const size_t		offset = 4 * (v * rtv->textures[texture_id].width + u);
	const t_color		color = {
		rtv->textures[texture_id].data[offset + 0],
		rtv->textures[texture_id].data[offset + 1],
		rtv->textures[texture_id].data[offset + 2],
	};

	if (rtv->textures[texture_id].data[offset + 3] == 0)
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
	if (!rtv->textures[rtv->spheres[intr->idx].texture_id].data)
		return ;
	_get_uv_sphere(rtv, params, intr, uv);
	return (_check_texture_sphere(rtv, params, intr, uv));
}
