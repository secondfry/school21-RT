/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 18:18:51 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_rtv(t_rtv *rtv)
{
	rtv->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	rtv->camera_position = vector_new(0.f, 0.f, 0.f, 1.f);
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
	t_rtv		rtv;
	t_mlx		mlx;

	// rtv.spheres[0] = (t_sphere) {
	// 	vector_new(1, 1, 5, 1),
	// 	color_new(255, 0, 0),
	// 	1.0f,
	// 	TRAIT_EXISTS
	// };
	// rtv.spheres[1] = (t_sphere) {
	// 	vector_new(-1, 1, 5, 1),
	// 	color_new(0, 255, 0),
	// 	1.0f,
	// 	TRAIT_EXISTS
	// };
	// rtv.spheres[2] = (t_sphere) {
	// 	vector_new(0, 0, 5, 1),
	// 	color_new(0, 0, 255),
	// 	1.0f,
	// 	TRAIT_EXISTS
	// };
	rtv.spheres[0] = (t_sphere) {
		vector_new(0, -1.f, 3, 1),
		color_new(255, 0, 0),
		1.0f,
		500.f,
		TRAIT_EXISTS
	};
	rtv.spheres[1] = (t_sphere) {
		vector_new(-2, 0, 4, 1),
		color_new(0, 255, 0),
		1.0f,
		10.f,
		TRAIT_EXISTS
	};
	rtv.spheres[2] = (t_sphere) {
		vector_new(2, 0, 4, 1),
		color_new(0, 0, 255),
		1.0f,
		500.f,
		TRAIT_EXISTS
	};
	rtv.spheres[3] = (t_sphere) {
		vector_new(0, -5001, 0, 1),
		color_new(255, 255, 0),
		5000.0f * 5000.0f,
		1000.f,
		TRAIT_EXISTS
	};

	rtv.plights[0] = (t_plight) {
		vector_new(2, 1, 0, 1),
		0.6f,
		TRAIT_EXISTS
	};

	rtv.dlights[0] = (t_dlight) {
		vector_new(1, 4, 4, 0),
		0.2f,
		TRAIT_EXISTS
	};
	// rtv.dlights[0] = (t_dlight) {
	// 	vector_new(4, 0, 5, 0),
	// 	0.4f,
	// 	TRAIT_EXISTS
	// };

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
