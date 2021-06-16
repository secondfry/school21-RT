/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:39:04 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/22 19:08:37 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

static float	get_angle(t_wolf *wolf)
{
	float	angle;

	angle = wolf->player->angle + \
		(float) wolf->column * (float) FOV / (float) WIDTH - FOV / 2;
	while (angle < -180)
		angle += 360;
	while (angle > 180)
		angle -= 360;
	return (angle);
}

static void	find_intersection(
	t_wolf *wolf,
	float angle,
	t_point dots[2]
)
{
	if (angle > -90 && angle < 90)
		dots[0] = intersection_horizontal(\
			wolf, angle, wolf->player->wall.prev.y - EPSILON);
	else
		dots[0] = intersection_horizontal(\
			wolf, angle, wolf->player->wall.next.y);
	if (angle > 0 && angle < 180)
		dots[1] = intersection_vertical(\
			wolf, angle, wolf->player->wall.next.x);
	else
		dots[1] = intersection_vertical(\
			wolf, angle, wolf->player->wall.prev.x - EPSILON);
}

static void	find_distance(
	t_wolf *wolf,
	t_point dots[2],
	float distance[2],
	float angle
)
{
	if (angle == 0 || angle == 180 || angle == -180)
		distance[0] = fabsf(dots[0].y - wolf->player->pos.y);
	else
		distance[0] = \
			(dots[0].x - wolf->player->pos.x) / sinf(angle * M_PI_F / 180);
	distance[1] = \
		(dots[1].x - wolf->player->pos.x) / sinf(angle * M_PI_F / 180);
}

void	loop_redraw(t_wolf *wolf)
{
	t_point		dots[2];
	float		distances[2];
	float		angle;

	if (!(wolf->flags & FLAG_REDRAW))
		return ;
	ft_bzero(wolf->mlx->img_data, wolf->mlx->size_line_char * HEIGHT);
	wolf->flags -= FLAG_REDRAW;
	wolf->column = 0;
	while (wolf->column < WIDTH)
	{
		angle = get_angle(wolf);
		find_intersection(wolf, angle, dots);
		find_distance(\
			wolf, dots, distances, angle);
		draw(wolf, angle, dots, distances);
		wolf->column++;
	}
	mlx_put_image_to_window(\
		wolf->mlx->mlx, wolf->mlx->win, wolf->mlx->img, 0, 0);
}
