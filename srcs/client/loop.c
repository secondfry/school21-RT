/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:49:20 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:46:20 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "loop_hook.h"
#include "client/main.h"
#include "loop/loop_sdl.h"

void	invalidate_sphere_vectors(t_rtv *rtv, t_sphere sphere)
{
	ft_putendl_fd("[invalidate_sphere_vectors] unimplemented", 2);
	(void)rtv;
	(void)sphere;
}

int	loop_key_hook(int keycode, t_rtv *rtv)
{
	(void)keycode;
	(void)rtv;
	return (0);
}

// FIXME(secondfry): clear texture okay son
static void	sdl_clear_texture(t_sdl *sdl)
{
	(void)sdl;
}

void	loop_redraw(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	sdl_clear_texture(rtv->sdl);
	rtv->flags -= FLAG_REDRAW;
	run_cluster(rtv);
}

int	loop_hook(t_rtv *rtv)
{
	loop_redraw(rtv);
	loop_sdl(rtv);
	return (0);
}
