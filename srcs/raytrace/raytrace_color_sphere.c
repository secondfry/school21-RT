/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_color_sphere.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:24:25 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 21:10:47 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace/raytrace_color_sphere.h"
#include "defines.h"
#include "rtv.h"
#include "vector.h"
#include "color.h"

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

static void	check_checkerboard_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr,
	double uv[2]
)
{
	const double	u = uv[0];
	const double	v = uv[1];

	(void)rtv;
	(void)intr;
	if (u < 0.5 && v < 0.5)
		return ;
	if (u >= 0.5 && v >= 0.5)
		return ;
	color_mult((t_color *)&params->color, 0.5);
}

static void	check_texture_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr,
	double uv[2]
)
{
	t_byte			texture_id;
	unsigned int	u;
	unsigned int	v;
	size_t			offset;
	t_color			color;

	if (!rtv->textures[rtv->spheres[intr->idx].texture_id].data)
		return ;
	texture_id = rtv->spheres[intr->idx].texture_id;
	u = uv[0] * rtv->textures[texture_id].width;
	v = uv[1] * rtv->textures[texture_id].height;
	offset = 4 * (v * rtv->textures[texture_id].width + u);
	if (rtv->textures[texture_id].data[offset + 3] == 0)
		return ;
	color = (t_color){
		rtv->textures[texture_id].data[offset + 0],
		rtv->textures[texture_id].data[offset + 1],
		rtv->textures[texture_id].data[offset + 2],
	};
	ft_memcpy((void *)&params->color, &color, sizeof(t_color));
}

void	check_color_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr
)
{
	double	uv[2];

	if (intr->idx > MAX_SPHERES - 1)
		return ;
	if (!(rtv->spheres[intr->idx].traits & TRAIT_TEXTURED) \
		&& !(rtv->spheres[intr->idx].traits & TRAIT_CHECKERBOARD) \
	)
		return ;
	_get_uv_sphere(rtv, params, intr, uv);
	if (rtv->spheres[intr->idx].traits & TRAIT_TEXTURED)
		check_texture_sphere(rtv, params, intr, uv);
	if (rtv->spheres[intr->idx].traits & TRAIT_CHECKERBOARD)
		check_checkerboard_sphere(rtv, params, intr, uv);
}
