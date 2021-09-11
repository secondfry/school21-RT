/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_color_sphere.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:24:25 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 23:29:15 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace/raytrace_color_sphere.h"
#include "defines.h"
#include "rtv.h"
#include "vector.h"
#include "color.h"
#include "raytrace/raytrace_perlin.h"
#include "raytrace/raytrace_sphere_uv.h"

static void	check_checkerboard_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr,
	double uv[2]
)
{
	const double	u = fmod(uv[0] * 4, 1);
	const double	v = fmod(uv[1] * 2, 1);

	(void)rtv;
	(void)intr;
	if (u < 0.5 && v < 0.5)
		return ;
	if (u >= 0.5 && v >= 0.5)
		return ;
	color_mult((t_color *)&params->color, 0.5);
}

static void	check_sin_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr,
	double uv[2]
)
{
	(void)rtv;
	(void)intr;
	color_add((t_color *)&params->color, &((t_color){\
		(uv[0] - uv[1]) * (uv[0] - uv[1]) * 255, \
		sin(uv[1] * M_PI / 2) * 255, \
		cos(uv[0] * M_PI / 2) * 255, \
	}));
}

static void	check_perlin_sphere(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr,
	double uv[2]
)
{
	static bool	once;

	(void)rtv;
	(void)intr;
	if (!once)
	{
		init_perlin();
		once = true;
	}
	color_mult(\
		(t_color *)&params->color, \
		(perlin(uv[0] * PERLIN_SIZE, uv[1] * PERLIN_SIZE) + 1) / 2 \
	);
	return ;
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
		&& !(rtv->spheres[intr->idx].traits & TRAIT_COLOR_COMPLICATED) \
		&& !(rtv->spheres[intr->idx].traits & TRAIT_COLOR_PERLIN) \
	)
		return ;
	get_uv_sphere(rtv, params, intr, uv);
	if (rtv->spheres[intr->idx].traits & TRAIT_TEXTURED)
		check_texture_sphere(rtv, params, intr, uv);
	if (rtv->spheres[intr->idx].traits & TRAIT_CHECKERBOARD)
		check_checkerboard_sphere(rtv, params, intr, uv);
	if (rtv->spheres[intr->idx].traits & TRAIT_COLOR_PERLIN)
		check_perlin_sphere(rtv, params, intr, uv);
	if (rtv->spheres[intr->idx].traits & TRAIT_COLOR_COMPLICATED)
		check_sin_sphere(rtv, params, intr, uv);
}
