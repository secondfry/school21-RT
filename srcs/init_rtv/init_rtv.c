/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rtv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:08:37 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 13:42:08 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_rtv.h"
#include "init_rtv/texture.h"

static void	init_rtv_scene(t_rtv *rtv)
{
	init_rtv_objects(rtv);
	init_rtv_lights(rtv);
}

static void	init_rtv_common(t_rtv *rtv)
{
	rtv->filter = 0;
	rtv->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	ft_memcpy(
		(void *)&rtv->camera_position, \
		&((t_vector_4){0.f, 0.f, -21.f, 1.f}), \
		sizeof(t_vector_4) \
	);
	vector_set_by_value(&rtv->camera_angles, vector_new(0, 0, 0, 0));
	rtv->camera_rotation = matrix_new_identity();
	rtv->filename = (void *)0;
	vector_set_by_value(&rtv->textures[0].scale, vector_new(-10, 0, 10, 0));
	vector_set_by_value(&rtv->textures[0].offset, vector_new(5, 0, 5, 0));
	load_texture("textures/error_guy.png", rtv->textures + 0);
	load_texture("textures/UVChecker_byValle_1K_8.png", rtv->textures + 1);
}

void	init_rtv(t_rtv *rtv)
{
	init_rtv_common(rtv);
	init_rtv_scene(rtv);
}
