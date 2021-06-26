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

static float	light(t_rtv *rtv, t_vector_4 P, t_vector_4 N)
{
	float	intensity;

	intensity = rtv->ambient;
	for (t_byte i = 0; i < MAX_PLIGHTS; i++) {
		if (!(rtv->plights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = vector_sub(rtv->plights[i].position, P);
		float dot = vector_dot(N, L);
		if (dot < 0)
			continue;
		float delta = rtv->plights[i].intensity *
			dot / vector_length(L);
		intensity += delta;
	}
	for (t_byte i = 0; i < MAX_DLIGHTS; i++) {
		if (!(rtv->dlights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = rtv->dlights[i].direction;
		float dot = vector_dot(N, L);
		if (dot < 0)
			continue;
		float delta = rtv->dlights[i].intensity *
			dot / vector_length(L);
		intensity += delta;
	}
	return intensity;
}

static void	check_sphere(t_rtv *rtv, t_byte idx, t_vector_4 D, float t[2])
{
	t_vector_4 O = rtv->camera_position;
	t_vector_4 C = rtv->spheres[idx].position;
	t_vector_4 CO = vector_sub(O, C);
	float r = rtv->spheres[idx].radius;
	float a = vector_dot(D, D);
	float b = 2 * vector_dot(D, CO);
	float c = vector_dot(CO, CO) - r * r; // float is not enough here
	float sqrt = b * b - 4 * a * c;
	if (sqrt < 0) {
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return;
	}
	t[0] = (-1 * b + sqrtf(sqrt)) / (2 * a);
	t[1] = (-1 * b - sqrtf(sqrt)) / (2 * a);
}

static t_color	raytrace(t_rtv *rtv, short xc, short yc, float t_min, float t_max)
{
	float t[2];
	t_vector_4 D = vector_new((float) xc / WIDTH, (float) yc / HEIGHT, 1, 0);
	float t_closest = 1.0 / 0.0;
	t_byte	idx = -1;

	for (t_byte i = 0; i < MAX_SPHERES; i++) {
		if (!(rtv->spheres[i].traits & TRAIT_EXISTS))
			continue;
		check_sphere(rtv, i, D, t);
		if (t[0] > t_min && t[0] < t_max && t[0] < t_closest) {
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > t_min && t[1] < t_max && t[1] < t_closest) {
			t_closest = t[1];
			idx = i;
		}
	}
	
	if (t_closest == 1.0 / 0.0) {
		return color_new(255, 255, 255);
	}

	// return rtv->spheres[idx].color;

	t_vector_4 O = rtv->camera_position;
	t_vector_4 P = vector_add(O, vector_mult(D, t_closest));
	t_vector_4 N = vector_sub(P, rtv->spheres[idx].position);
	vector_normalize(N);

	float intensity = light(rtv, P, N);

	return color_mult(rtv->spheres[idx].color, intensity);
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
