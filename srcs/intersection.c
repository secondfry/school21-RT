/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:03:51 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/22 18:51:24 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static t_byte	is_wall(t_wolf *wolf, unsigned short x, unsigned short y)
{
	x /= 64;
	y /= 64;
	if (x > wolf->map_width)
		return (2);
	if (y > wolf->map_height)
		return (2);
	return (wolf->map[wolf->map_width * y + x] == '1');
}

static void	horizontal_increment(float *wall_x, float *wall_y, float angle)
{
	if (angle > -90 && angle < 90)
		*wall_y -= 64;
	else
		*wall_y += 64;
	if (angle > 0 && angle < 180)
		*wall_x += 64 * fabsf(tanf(angle * M_PI_F / 180));
	else
		*wall_x -= 64 * fabsf(tanf(angle * M_PI_F / 180));
}

t_point	intersection_horizontal(t_wolf *wolf, float angle, float wall_y)
{
	float			dy;
	float			dx;
	float			wall_x;
	t_byte			check;

	if ((90 - EPSILON < angle && angle < 90 + EPSILON)
		|| (-90 - EPSILON < angle && angle < -90 + EPSILON))
		return ((t_point){0, 0});
	dy = wolf->player->pos.y - wall_y;
	dx = dy * tanf(angle * M_PI_F / 180);
	wall_x = dx + wolf->player->pos.x;
	check = is_wall(wolf, wall_x, wall_y);
	while (check == 0)
	{
		horizontal_increment(&wall_x, &wall_y, angle);
		check = is_wall(wolf, wall_x, wall_y);
	}
	if (check == 1)
		return ((t_point){wall_x, wall_y});
	return ((t_point){0, 0});
}

static void	vertical_increment(float *wall_x, float *wall_y, float angle)
{
	if (angle > 0 && angle < 180)
		*wall_x += 64;
	else
		*wall_x -= 64;
	if (angle > -90 && angle < 90)
		*wall_y -= 64 / fabsf(tanf(angle * M_PI_F / 180));
	else
		*wall_y += 64 / fabsf(tanf(angle * M_PI_F / 180));
}

t_point	intersection_vertical(t_wolf *wolf, float angle, float wall_x)
{
	float			dy;
	float			dx;
	float			wall_y;
	t_byte			check;

	if ((-EPSILON < angle && angle < EPSILON)
		|| (-180 - EPSILON < angle && angle < -180 + EPSILON)
		|| (180 - EPSILON < angle && angle < 180 + EPSILON))
		return ((t_point){0, 0});
	dx = wolf->player->pos.x - wall_x;
	dy = dx / tanf(angle * M_PI_F / 180);
	wall_y = dy + wolf->player->pos.y;
	check = is_wall(wolf, wall_x, wall_y);
	while (check == 0)
	{
		vertical_increment(&wall_x, &wall_y, angle);
		check = is_wall(wolf, wall_x, wall_y);
	}
	if (check == 1)
		return ((t_point){wall_x, wall_y});
	return ((t_point){0, 0});
}
