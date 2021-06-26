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
	rtv->camera_position = vector_new(0.f, 0.f, 0.f, 1);
	rtv->camera_rotation = vector_new(0.f, 0.f, 0.f, 1);
}

void	check_defines(void)
{
	if ((WIDTH < 240 || WIDTH > 1920) ||
		(HEIGHT < 240 || HEIGHT > 1080))
		graceful(ERR_INVALID_DEFINE, ERR_INVALID_DEFINE_MSG);
}

int	main(void)
{
	t_rtv		rtv;
	t_mlx		mlx;

	t_sphere	s1 = {
		vector_new(1, 1, 5, 1),
		color_new(255, 0, 0),
		1.0f,
		TRAIT_EXISTS
	};
	rtv.spheres[0] = s1;
	t_sphere	s2 = {
		vector_new(-1, 1, 5, 1),
		color_new(0, 255, 0),
		1.0f,
		TRAIT_EXISTS
	};
	rtv.spheres[1] = s2;
	t_sphere	s3 = {
		vector_new(0, 0, 5, 1),
		color_new(0, 0, 255),
		1.0f,
		TRAIT_EXISTS
	};
	rtv.spheres[2] = s3;

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
