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
	t_vector_4 C = rtv->spheres[idx].position;
	t_vector_4 CO = vector_sub(O, C);
	float a = vector_dot(D, D);
	float b = 2 * vector_dot(D, CO);
	float c = vector_dot(CO, CO) - rtv->spheres[idx].radius_squared; // float is not enough here

	free(CO);

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
	t_byte	sphere_idx;
}				t_intersection_sphere_closest;

static t_intersection_sphere_closest	intersection_sphere_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
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
	float		intensity;
	float		dot;
	t_vector_4	tmp;

	intensity = 0;
	for (t_byte i = 0; i < MAX_PLIGHTS; i++) {
		if (!(rtv->plights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = vector_sub(rtv->plights[i].position, P);
		t_intersection_sphere_closest res = intersection_sphere_closest(rtv, P, L, EPSILON, 1.f);
		if (res.distance != 1.0 / 0.0) {
			free(L);
			continue;
		}
		dot = vector_dot(N, L);
		if (dot > 0) {
			float delta = rtv->plights[i].intensity *
				dot / vector_length(L);
			intensity += delta;
		}
		if (specular == -1) {
			free(L);
			continue;
		}
		tmp = vector_mult(N, 2 * vector_dot(N, L));
		t_vector_4 R = vector_sub(tmp, L);
		free(tmp);
		dot = vector_dot(R, V);
		if (dot > 0) {
			float delta = rtv->plights[i].intensity *
				powf(dot / vector_length(R) / vector_length(V), specular);
			intensity += delta;
		}
		free(L);
		free(R);
	}
	return intensity;
}

static float	light_directional(t_rtv *rtv, t_vector_4 P, t_vector_4 N, t_vector_4 V, float specular)
{
	float		intensity;
	float		dot;
	t_vector_4	tmp;

	intensity = 0;
	for (t_byte i = 0; i < MAX_DLIGHTS; i++) {
		if (!(rtv->dlights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = rtv->dlights[i].direction;
		t_intersection_sphere_closest res = intersection_sphere_closest(rtv, P, L, EPSILON, 1.0 / 0.0);
		if (res.distance != 1.0 / 0.0)
			continue;
		dot = vector_dot(N, L);
		if (dot > 0) {
			float delta = rtv->dlights[i].intensity *
				dot / vector_length(L);
			intensity += delta;
		}
		if (specular == -1)
			continue;
		tmp = vector_mult(N, 2 * vector_dot(N, L));
		t_vector_4 R = vector_sub(tmp, L);
		free(tmp);
		dot = vector_dot(R, V);
		if (dot > 0) {
			float delta = rtv->dlights[i].intensity *
				powf(dot / vector_length(R) / vector_length(V), specular);
			intensity += delta;
		}
		free(R);
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
	t_vector_4	tmp;

	t_intersection_sphere_closest res = intersection_sphere_closest(rtv, O, D, t_min, t_max);
	if (res.distance == 1.0 / 0.0)
		return color_new(255, 255, 255);
	tmp = vector_mult(D, res.distance);
	t_vector_4 P = vector_add(O, tmp);
	free(tmp);
	t_vector_4 N = vector_sub(P, rtv->spheres[res.sphere_idx].position);
	vector_normalize(N);
	t_vector_4 V = vector_mult(D, -1);
	float intensity = light(rtv, P, N, V, rtv->spheres[res.sphere_idx].specular);

	free(P);
	free(N);
	free(V);

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
	t_color 	color;
	t_vector_4	tmp;

	t_vector_4 O = rtv->camera_position;
	tmp = vector_new((float) xc / WIDTH, (float) yc / HEIGHT, 1.f, 0);
	t_vector_4 D = matrix_on_vector(rtv->camera_rotation, tmp);
	free(tmp);
	color = raytrace(rtv, O, D, 1.0f, 1.0 / 0.0);
	canvas_to_screen(rtv, xc, yc, color);
	
	free(D);
	free(color);
}

#include <pthread.h>

typedef struct	s_params {
	t_rtv *rtv;
	short ya;
	short yb;
	short xa;
	short xb;
}				t_params;

#define THREAD_COUNT 8

void	*hello(void *params) {
    for (short yc = ((t_params *)params)->ya; yc <= ((t_params *)params)->yb; yc++) {
		for (short xc = ((t_params *)params)->xa; xc < ((t_params *)params)->xb; xc++) {
			process_pixel(((t_params *)params)->rtv, xc, yc);
		}
	}
	
    pthread_exit(NULL);
}

void	loop_redraw(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	ft_bzero(rtv->mlx->img_data, rtv->mlx->size_line_char * HEIGHT);
	rtv->flags -= FLAG_REDRAW;

	pthread_t	tid[THREAD_COUNT];
	t_params	param[THREAD_COUNT];
	short		ya = -1 * HEIGHT / 2;
	short		xa = -1 * WIDTH / 2;
	for (t_byte y = 0; y < 2; y++) {
		for (t_byte x = 0; x < 4; x++) {
			param[y * 4 + x] = (t_params) {
				rtv,
				ya + y * HEIGHT / 2,
				ya + (y + 1) * HEIGHT / 2,
				xa + x * WIDTH / 4,
				xa + (x + 1) * WIDTH / 4
			};
		}
	}
	param[0] = (t_params) {
		rtv,
		ya + 1,
		ya + HEIGHT / 2,
		xa,
		xa + WIDTH / 4
	};
	for (t_byte i = 0; i < THREAD_COUNT; i++) {
    	pthread_create(&tid[i], NULL, hello, &param[i]);
	}
	for (t_byte i = 0; i < THREAD_COUNT; i++) {
    	pthread_join(tid[i], NULL);
	}

	// for (short yc = -1 * HEIGHT / 2 + 1; yc <= HEIGHT / 2; yc++) {
	// 	for (short xc = -1 * WIDTH / 2; xc < WIDTH / 2; xc++) {
	// 		process_pixel(rtv, xc, yc);
	// 	}
	// }
	mlx_put_image_to_window(\
		rtv->mlx->mlx, rtv->mlx->win, rtv->mlx->img, 0, 0);
}
