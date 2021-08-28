/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_common.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 22:16:36 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/28 15:13:41 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

void	canvas_to_screen(t_rtv *rtv, short xc, short yc, t_color color)
{
	t_ushort	xs;
	t_ushort	ys;
	size_t		offset;

	xs = WIDTH / 2 + xc;
	ys = HEIGHT / 2 - yc;
	offset = ys * rtv->sdl->pitch + xs * 4;
	rtv->sdl->buffer[offset++] = color.blue;
	rtv->sdl->buffer[offset++] = color.green;
	rtv->sdl->buffer[offset++] = color.red;
	rtv->sdl->buffer[offset] = 0;
}
