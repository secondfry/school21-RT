/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:49:20 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/17 21:08:40 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"
#include "client/main.h"

int	loop_key_hook(int keycode, t_rtv *rtv)
{
	(void)keycode;
	(void)rtv;
	return (0);
}

void	loop_redraw(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	ft_bzero(rtv->mlx->img_data, rtv->mlx->size_line_char * HEIGHT);
	rtv->flags -= FLAG_REDRAW;
	run_cluster(rtv);
	mlx_put_image_to_window(\
		rtv->mlx->mlx, rtv->mlx->win, rtv->mlx->img, 0, 0);
}

void	loop_before_next_update(t_rtv *rtv)
{
	mlx_do_sync(rtv->mlx->mlx);
}

int	loop_hook(t_rtv *rtv)
{
	loop_redraw(rtv);
	loop_before_next_update(rtv);
	return (0);
}
