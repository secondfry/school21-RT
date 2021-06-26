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

static void	intersection_sphere(t_rtv *rtv, t_vector_4 O, t_vector_4 D, t_byte idx, float t[2])
{
	float r = rtv->spheres[idx].radius;
	t_vector_4 C = rtv->spheres[idx].position;
	t_vector_4 CO = vector_sub(O, C);
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

typedef struct	s_intersection_sphere_closest
{
	float	distance;
	char	sphere_idx;
}				t_intersection_sphere_closest;

static t_intersection_sphere_closest	intersection_sphere_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max)
{
	float t_closest = 1.0 / 0.0;
	char idx = -1;
	float t[2];

	for (t_byte i = 0; i < MAX_SPHERES; i++) {
		if (!(rtv->spheres[i].traits & TRAIT_EXISTS))
			continue;
		intersection_sphere(rtv, O, D, i, t);
		if (t[0] > t_min && t[0] < t_max && t[0] < t_closest) {
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > t_min && t[1] < t_max && t[1] < t_closest) {
			t_closest = t[1];
			idx = i;
		}
	}
	return ((t_intersection_sphere_closest) { t_closest, idx });
}

static float	light_point(t_rtv *rtv, t_vector_4 P, t_vector_4 N, t_vector_4 V, float specular)
{
	float	intensity;
	float	dot;

	intensity = 0;
	for (t_byte i = 0; i < MAX_PLIGHTS; i++) {
		if (!(rtv->plights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = vector_sub(rtv->plights[i].position, P);
		t_intersection_sphere_closest res = intersection_sphere_closest(rtv, P, L, EPSILON, 1.f);
		if (res.sphere_idx != -1)
			continue;
		dot = vector_dot(N, L);
		if (dot > 0) {
			float delta = rtv->plights[i].intensity *
				dot / vector_length(L);
			intensity += delta;
		}
		if (specular == -1)
			continue;
		t_vector_4 R = vector_sub(vector_mult(N, 2 * vector_dot(N, L)), L);
		dot = vector_dot(R, V);
		if (dot > 0) {
			float delta = rtv->plights[i].intensity *
				powf(dot / vector_length(R) / vector_length(V), specular);
			intensity += delta;
		}
	}
	return intensity;
}

static float	light_directional(t_rtv *rtv, t_vector_4 P, t_vector_4 N, t_vector_4 V, float specular)
{
	float	intensity;
	float	dot;

	intensity = 0;
	for (t_byte i = 0; i < MAX_DLIGHTS; i++) {
		if (!(rtv->dlights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = rtv->dlights[i].direction;
		t_intersection_sphere_closest res = intersection_sphere_closest(rtv, P, L, EPSILON, 1.0 / 0.0);
		if (res.sphere_idx != -1)
			continue;
		dot = vector_dot(N, L);
		if (dot > 0) {
			float delta = rtv->dlights[i].intensity *
				dot / vector_length(L);
			intensity += delta;
		}
		if (specular == -1)
			continue;
		t_vector_4 R = vector_sub(vector_mult(N, 2 * vector_dot(N, L)), L);
		dot = vector_dot(R, V);
		if (dot > 0) {
			float delta = rtv->dlights[i].intensity *
				powf(dot / vector_length(R) / vector_length(V), specular);
			intensity += delta;
		}
	}
	return intensity;
}

static float	light(t_rtv *rtv, t_vector_4 P, t_vector_4 N, t_vector_4 V, float specular)
{
	float	intensity;

	intensity = rtv->ambient +\
		light_point(rtv, P, N, V, specular) +\
		light_directional(rtv, P, N, V, specular);
	return intensity;
}

static t_color	raytrace(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max)
{
	t_intersection_sphere_closest res = intersection_sphere_closest(rtv, O, D, t_min, t_max);
	if (res.sphere_idx == -1)
		return color_new(255, 255, 255);
	t_vector_4 P = vector_add(O, vector_mult(D, res.distance));
	t_vector_4 N = vector_sub(P, rtv->spheres[res.sphere_idx].position);
	vector_normalize(N);

	float intensity = light(rtv, P, N, vector_mult(D, -1), rtv->spheres[res.sphere_idx].specular);

	return color_mult(rtv->spheres[res.sphere_idx].color, intensity);
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

	t_vector_4 O = rtv->camera_position;
	t_vector_4 D = vector_new((float) xc / WIDTH, (float) yc / HEIGHT, 1.f, 0);
	color = raytrace(rtv, O, D, 1.0f, 1.0 / 0.0);
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
