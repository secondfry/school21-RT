/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:49:20 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 18:28:41 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"
#include "loop/loop_sdl.h"
#include "sdl/sdl_clear_texture.h"

void	invalidate_sphere_vectors(t_rtv *rtv, t_sphere sphere)
{
	ft_putendl_fd("[invalidate_sphere_vectors] unimplemented", 2);
	(void)rtv;
	(void)sphere;
}

void	loop_invalidate_position(t_rtv *rtv)
{
	ft_putendl_fd("[loop_invalidate_position] unimplemented", 2);
	(void)rtv;
}

void	loop_invalidate_rotation(t_rtv *rtv)
{
	ft_putendl_fd("[loop_invalidate_rotation] unimplemented", 2);
	(void)rtv;
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
