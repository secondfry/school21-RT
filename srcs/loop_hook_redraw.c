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

static float	get_angle(t_rtv *rtv)
{
	float	angle;

	angle = (float) rtv->column * (float) FOV / (float) WIDTH - FOV / 2;
	while (angle < -180)
		angle += 360;
	while (angle > 180)
		angle -= 360;
	return (angle);
}

static void	find_intersection(
	t_rtv *rtv,
	float angle,
	t_point dots[2]
)
{
	(void)rtv;
	(void)angle;
	dots[0] = (t_point){0, 0};
	dots[1] = (t_point){0, 0};
}

static void	find_distance(
	t_rtv *rtv,
	t_point dots[2],
	float distance[2],
	float angle
)
{
	(void)rtv;
	(void)angle;
	(void)dots;
	distance[0] = 0;
	distance[1] = 0;
}

void	loop_redraw(t_rtv *rtv)
{
	t_point		dots[2];
	float		distances[2];
	float		angle;

	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	ft_bzero(rtv->mlx->img_data, rtv->mlx->size_line_char * HEIGHT);
	rtv->flags -= FLAG_REDRAW;
	rtv->column = 0;
	while (rtv->column < WIDTH)
	{
		angle = get_angle(rtv);
		find_intersection(rtv, angle, dots);
		find_distance(\
			rtv, dots, distances, angle);
		draw(rtv, angle, dots, distances);
		rtv->column++;
	}
	mlx_put_image_to_window(\
		rtv->mlx->mlx, rtv->mlx->win, rtv->mlx->img, 0, 0);
}
