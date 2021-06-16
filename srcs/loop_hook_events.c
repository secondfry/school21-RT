/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:59:41 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/22 18:52:06 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

static void	move(t_rtv *rtv, char direction)
{
	rtv->player->pos.x += \
		direction * sinf(rtv->player->angle * M_PI_F / 180) * 5;
	rtv->player->pos.y -= \
		direction * cosf(rtv->player->angle * M_PI_F / 180) * 5;
	rtv->flags |= FLAG_INVALIDATE_POSITION;
}

static void	strafe(t_rtv *rtv, char direction)
{
	rtv->player->pos.x += \
		sinf((direction * 90 + rtv->player->angle) * M_PI_F / 180) * 5;
	rtv->player->pos.y -= \
		cosf((direction * 90 + rtv->player->angle) * M_PI_F / 180) * 5;
	rtv->flags |= FLAG_INVALIDATE_POSITION;
}

static void	rotate(t_rtv *rtv, char direction)
{
	rtv->player->angle += 3 * direction;
	if (rtv->player->angle > 180)
		rtv->player->angle -= 360;
	if (rtv->player->angle < -180)
		rtv->player->angle += 360;
	rtv->flags |= FLAG_INVALIDATE_ROTATION;
}

static void	toggle_art(t_rtv *rtv)
{
	rtv->options ^= OPTION_ART;
	rtv->flags |= FLAG_REDRAW;
}

int	loop_key_hook(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_ESC)
		loop_destroy_hook(rtv);
	if (keycode == KEY_W)
		move(rtv, 1);
	if (keycode == KEY_S)
		move(rtv, -1);
	if (keycode == KEY_Q)
		strafe(rtv, -1);
	if (keycode == KEY_E)
		strafe(rtv, 1);
	if (keycode == KEY_A)
		rotate(rtv, -1);
	if (keycode == KEY_D)
		rotate(rtv, 1);
	if (keycode == KEY_F)
		toggle_art(rtv);
	return (0);
}
