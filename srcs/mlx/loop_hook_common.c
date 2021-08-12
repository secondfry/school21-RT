/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_common.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 22:16:36 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/12 22:16:37 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

void	canvas_to_screen(t_rtv *rtv, short xc, short yc, t_color color)
{
	t_ushort	xs;
	t_ushort	ys;

	xs = WIDTH / 2 + xc;
	ys = HEIGHT / 2 - yc;
	rtv->mlx->img_data[ys * rtv->mlx->size_line_int + xs] = \
		color_to_int(color);
}
