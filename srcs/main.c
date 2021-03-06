/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:11:10 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "sdl/init_sdl.h"
#include "imgui/imgui_init.h"

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

	check_defines();
	init_rtv(&rtv);
	parser(&rtv, argc, argv);
	status = sdl_init(&sdl);
	if (status)
		return (status);
	rtv.sdl = &sdl;
	imgui_init(&sdl, &imgui);
	sdl_loop(&rtv, &sdl);
	imgui_clear(&imgui);
	sdl_clear(&sdl);
	return (0);
}
