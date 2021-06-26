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

static void	check_sphere(t_rtv *rtv, t_vector_4 D, float t[2])
{
	(void)rtv;
	// t_vector_4 O = rtv->camera_position;
	t_vector_4 CO = vector_new(-1, -1, -5, 0); // gde sphere - gde camera);
	float r = 1; // sphere radius
	float a = dot(D, D);
	float b = 2 * dot(D, CO);
	float c = dot(CO, CO) - r * r;
	float sqrt = b * b - 4 * a * c;
	if (sqrt < 0) {
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return;
	}
	t[0] = -1 * b + sqrtf(sqrt) / (2 * a);
	t[1] = -1 * b - sqrtf(sqrt) / (2 * a);
}

static t_color	raytrace(t_rtv *rtv, short xc, short yc, float t_min, float t_max)
{
	float t[2];
	t_vector_4 D = vector_new((float) xc / WIDTH, (float) yc / HEIGHT, 1, 0);
	float t_closest = 1.0 / 0.0;

	check_sphere(rtv, D, t);
	if (t[0] > t_min && t[0] < t_max && t[0] < t_closest) {
		t_closest = t[0];
	}
	if (t[1] > t_min && t[1] < t_max && t[1] < t_closest) {
		t_closest = t[1];
	}
	if (t_closest == 1.0 / 0.0) {
		return color_new(0, 255, 255);
	}
	return color_new(0, 0, 255);
	// plups
	// gg
}

static void canvas_to_screen(t_rtv *rtv, short xc, short yc, t_color color)
{
	t_ushort	xs;
	t_ushort	ys;

	xs = WIDTH / 2 + xc;
	ys = HEIGHT / 2 - yc;
	rtv->mlx->img_data[ys * rtv->mlx->size_line_int + xs] = color_to_int(color);
}

static void	process_pixel(t_rtv *rtv, short xc, short yc)
{
	t_color	color;

	color = raytrace(rtv, xc, yc, 1.0f, 1.0 / 0.0);
	canvas_to_screen(rtv, xc, yc, color);
}

void	loop_redraw(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	ft_bzero(rtv->mlx->img_data, rtv->mlx->size_line_char * HEIGHT);
	rtv->flags -= FLAG_REDRAW;
	for (short yc = -1 * HEIGHT / 2 + 1; yc <= HEIGHT / 2; yc++) {
		for (short xc = -1 * WIDTH / 2; xc < WIDTH / 2; xc++) {
			process_pixel(rtv, xc, yc);
		}
	}
	mlx_put_image_to_window(\
		rtv->mlx->mlx, rtv->mlx->win, rtv->mlx->img, 0, 0);
}
