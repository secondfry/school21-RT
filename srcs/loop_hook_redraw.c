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

static void	check_sphere(t_rtv *rtv, short cxy[2], float t[2])
{
	t_vector_4 O = rtv->camera_position;
	t_vector_4 D = vector_new(cxy[1] / HEIGHT, cxy[0] / HEIGHT, 1, 1);
	t_vector_4 CO = vector_new(-1, -1, -5, 1); // gde sphere - gde camera);
	float r = 1; // sphere radius
	float a = dot(D, D);
	float b = 2 * dot(D, CO);
	float c = dot(CO, CO) - r * r;
	float sqrt = b * b - 4 * a * c;
	if (sqrt < 0) {
		t[0] = DOHUYA;
		t[1] = DOHUYA;
	}
}

static t_color	raytrace(t_rtv *rtv, short xc, short yc)
{
	t_vector_4 O = rtv->camera_position;
	t_vector_4 D = vector_new(xc / HEIGHT, yc / HEIGHT, 1, 1);
	t_vector_4 CO = vector_new(0, 0, 0, 1); // gde sphere - gde camera);
	float r = 1; // sphere radius
	float a = dot(D, D);
	float b = 2 * dot(D, CO);
	float c = dot(CO, CO) - r * r;
	float sqrt = b * b - 4 * a * c;
	if (sqrt < 0) {

	}
	// discriminant
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

	color = vector_new(rtv, xc, yc);
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
