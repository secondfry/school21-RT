/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/06/27 16:56:33 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_rtv(t_rtv *rtv)
{
	rtv->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	ft_memcpy((void *) &rtv->camera_position, &((t_vector_4) { 0.f, 0.f, 0.f, 1.f }), sizeof(t_vector_4));
	rtv->camera_angles[AROLL] = 0;
	rtv->camera_angles[AYAW] = 0;
	rtv->camera_angles[APITCH] = 0;
	rtv->camera_rotation = matrix_new_identity();
}

void	check_defines(void)
{
	if ((WIDTH < 1 || WIDTH > 1920) ||
		(HEIGHT < 1 || HEIGHT > 1080))
		graceful(ERR_INVALID_DEFINE, ERR_INVALID_DEFINE_MSG);
}

int	main(void)
{
	t_rtv	rtv;
	t_mlx	mlx;

	for (t_byte i = 0; i < MAX_SPHERES; i++) {
		ft_memcpy(rtv.spheres + i, &((t_sphere) {
			{{ 0, 0, 0, 0 }},
			0,
			0,
			0,
			0
		}), sizeof(t_sphere));
	}
	ft_memcpy(rtv.spheres + 0, &((t_sphere) {
		{{ 0, -1.f, 3, 1 }},
		color_new(255, 0, 0),
		1.0f,
		500.f,
		TRAIT_EXISTS
	}), sizeof(t_sphere));
	ft_memcpy(rtv.spheres + 1, &((t_sphere) {
		{{ -2, 0, 4, 1 }},
		color_new(0, 255, 0),
		1.0f,
		10.f,
		TRAIT_EXISTS
	}), sizeof(t_sphere));
	ft_memcpy(rtv.spheres + 2, &((t_sphere) {
		{{ 2, 0, 4, 1 }},
		color_new(0, 0, 255),
		1.0f,
		500.f,
		TRAIT_EXISTS
	}), sizeof(t_sphere));
	// ft_memcpy(rtv.spheres + 3, &((t_sphere) {
	// 	{{ 0, -5001, 0, 1 }},
	// 	color_new(255, 255, 0),
	// 	5000.0f * 5000.0f,
	// 	1000.f,
	// 	TRAIT_EXISTS
	// }), sizeof(t_sphere));

	for (t_byte i = 0; i < MAX_PLANES; i++) {
		ft_memcpy(rtv.planes + i, &((t_plane) {
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			0,
			0,
			0
		}), sizeof(t_plane));
	}
	ft_memcpy(rtv.planes + 0, &((t_plane) {
		vector_new(0, -1.f, 0, 1),
		vector_new(0, -1.f, 0, 1),
		color_new(255, 255, 0),
		1000.0f,
		TRAIT_EXISTS
	}), sizeof(t_plane));

	for (t_byte i = 0; i < MAX_PLIGHTS; i++) {
		ft_memcpy(rtv.plights + i, &((t_plight) {
			{ 0, 0, 0, 0 },
			0,
			0
		}), sizeof(t_plight));
	}
	ft_memcpy(rtv.plights + 0, &((t_plight) {
		{ 2, 1, 0, 1 },
		0.6f,
		TRAIT_EXISTS
	}), sizeof(t_plight));

	for (t_byte i = 0; i < MAX_DLIGHTS; i++) {
		ft_memcpy(rtv.dlights + i, &((t_dlight) {
			{ 0, 0, 0, 0 },
			0,
			0
		}), sizeof(t_dlight));
	}
	ft_memcpy(rtv.dlights + 0, &((t_dlight) {
		vector_new(1, 4, 4, 0),
		0.2f,
		TRAIT_EXISTS
	}), sizeof(t_dlight));

	rtv.ambient = 0.2f;

	check_defines();
	// parser(&rtv, fd);
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	rtv.mlx = &mlx;
	init_rtv(&rtv);
	init_mlx_hooks(&rtv);
	mlx_loop(mlx.mlx);
	return (0);
}
