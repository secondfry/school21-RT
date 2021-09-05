/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:11:12 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "typedef_common.h"
#include "init_rtv.h"
#include "loop_hook.h"
#include "client/main.h"
#include "sdl/init_sdl.h"
#include "client/network_prepare.h"

void	run_cluster(t_rtv *rtv)
{
	cluster_request(rtv);
}

int	main(void)
{
	t_rtv	rtv;
	t_sdl	sdl;
	t_imgui	imgui;
	int		status;

	init_rtv(&rtv);
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
