/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:59:41 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/17 18:02:13 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

static void	loop_movement(t_rtv *rtv, t_vector_4 direction)
{
	vector_set_by_value(&rtv->camera_position, vector_add(\
		rtv->camera_position, \
		matrix_on_vector(\
			rtv->camera_rotation, \
			direction \
		) \
	));
	rtv->flags |= FLAG_INVALIDATE_POSITION;
}

int	loop_key_hook(int keycode, t_rtv *rtv)
{
	if (keycode == KEY_ESC)
		loop_destroy_hook(rtv);
	if (keycode == KEY_R)
		rtv->flags |= FLAG_REDRAW;
	if (keycode == KEY_A)
	{
		rtv->camera_angles[AYAW] += M_PI_4F;
		rtv->flags |= FLAG_INVALIDATE_ROTATION;
	}
	if (keycode == KEY_D)
	{
		rtv->camera_angles[AYAW] -= M_PI_4F;
		rtv->flags |= FLAG_INVALIDATE_ROTATION;
	}
	if (keycode == KEY_W)
		loop_movement(rtv, (t_vector_4){0.0f, 0.0f, 1.0f, 0.0f});
	if (keycode == KEY_S)
		loop_movement(rtv, (t_vector_4){0.0f, 0.0f, -1.0f, 0.0f});
	if (keycode == KEY_Q)
		loop_movement(rtv, (t_vector_4){-1.0f, 0.0f, 0.0f, 0.0f});
	if (keycode == KEY_E)
		loop_movement(rtv, (t_vector_4){1.0f, 0.0f, 0.0f, 0.0f});
	return (0);
}
