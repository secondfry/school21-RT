/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/28 14:46:37 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "init_sdl.h"

void	check_defines(void)
{
	if ((WIDTH < 1 || WIDTH > 1920)
		|| (HEIGHT < 1 || HEIGHT > 1080)
	)
		graceful(ERR_INVALID_DEFINE, ERR_INVALID_DEFINE_MSG);
}

/**
 *	Точка входа в приложение
 */
int	main(int argc, char **argv)
{
	t_rtv	rtv;
	t_sdl	sdl;
	t_imgui	imgui;
	int		status;
	// t_mlx	mlx;

	check_defines();
	init_rtv(&rtv);
	parser(&rtv, argc, argv);
	status = sdl_init(&sdl);
	if (status)
		return (status);
	rtv.sdl = &sdl;
	imgui_init(&sdl, &imgui);
	sdl_loop(&rtv, &sdl);
	// init_mlx(&mlx);
	// init_mlx_image(&mlx);
	// rtv.mlx = &mlx;
	// init_mlx_hooks(&rtv);
	// mlx_loop(mlx.mlx);
	imgui_clear(&imgui);
	sdl_clear(&sdl);
	return (0);
}
