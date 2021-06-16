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

static void	move(t_wolf *wolf, char direction)
{
	wolf->player->pos.x += \
		direction * sinf(wolf->player->angle * M_PI_F / 180) * 5;
	wolf->player->pos.y -= \
		direction * cosf(wolf->player->angle * M_PI_F / 180) * 5;
	wolf->flags |= FLAG_INVALIDATE_POSITION;
}

static void	strafe(t_wolf *wolf, char direction)
{
	wolf->player->pos.x += \
		sinf((direction * 90 + wolf->player->angle) * M_PI_F / 180) * 5;
	wolf->player->pos.y -= \
		cosf((direction * 90 + wolf->player->angle) * M_PI_F / 180) * 5;
	wolf->flags |= FLAG_INVALIDATE_POSITION;
}

static void	rotate(t_wolf *wolf, char direction)
{
	wolf->player->angle += 3 * direction;
	if (wolf->player->angle > 180)
		wolf->player->angle -= 360;
	if (wolf->player->angle < -180)
		wolf->player->angle += 360;
	wolf->flags |= FLAG_INVALIDATE_ROTATION;
}

static void	toggle_art(t_wolf *wolf)
{
	wolf->options ^= OPTION_ART;
	wolf->flags |= FLAG_REDRAW;
}

int	loop_key_hook(int keycode, t_wolf *wolf)
{
	if (keycode == KEY_ESC)
		loop_destroy_hook(wolf);
	if (keycode == KEY_W)
		move(wolf, 1);
	if (keycode == KEY_S)
		move(wolf, -1);
	if (keycode == KEY_Q)
		strafe(wolf, -1);
	if (keycode == KEY_E)
		strafe(wolf, 1);
	if (keycode == KEY_A)
		rotate(wolf, -1);
	if (keycode == KEY_D)
		rotate(wolf, 1);
	if (keycode == KEY_F)
		toggle_art(wolf);
	return (0);
}
