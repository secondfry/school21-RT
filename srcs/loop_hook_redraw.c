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
		t_intersection res = intersection_sphere_closest(rtv, P, L, EPSILON, 1.f);
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
		t_intersection res = intersection_sphere_closest(rtv, P, L, EPSILON, 1.0 / 0.0);
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

static t_intersection	intersect_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max)
{
	t_intersection	results[2];
	t_intersection	res;

	res.distance = 1.0 / 0.0;
	results[ISPHERE] = intersection_sphere_closest(rtv, O, D, t_min, t_max);
	if (results[ISPHERE].distance < res.distance)
		res = results[ISPHERE];
	results[IPLANE] = intersection_plane_closest(rtv, O, D, t_min, t_max);
	if (results[IPLANE].distance < res.distance)
		res = results[IPLANE];
	return res;
}

static t_color	raytrace(t_rtv *rtv, t_vector_4 vectors[MAX_VECTORS], float t_min, float t_max)
{
	t_vector_4		tmp;
	t_intersection	res;

	res = intersect_closest(rtv, vectors[VCTR_O], vectors[VCTR_D], t_min, t_max);
	if (res.distance == 1.0 / 0.0)
		return color_new(255, 255, 255);
	tmp = vector_mult(vectors[VCTR_D], res.distance);
	t_vector_4 P = vector_add(vectors[VCTR_O], tmp);
	free(tmp);
	t_vector_4 N = vector_sub(P, rtv->spheres[res.idx].position);
	vector_normalize(N);
	t_vector_4 V = vector_mult(vectors[VCTR_D], -1);
	float intensity = light(rtv, P, N, V, rtv->spheres[res.idx].specular);

	free(P);
	free(N);
	free(V);

	return color_mult(rtv->spheres[res.idx].color, intensity);
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
	t_vector_4	vectors[MAX_VECTORS];

	vectors[VCTR_O] = rtv->camera_position;
	tmp = vector_new((float) xc / WIDTH, (float) yc / HEIGHT, 1.f, 0);
	vectors[VCTR_D] = matrix_on_vector(rtv->camera_rotation, tmp);
	free(tmp);
	color = raytrace(rtv, vectors, 1.0f, 1.0 / 0.0);
	canvas_to_screen(rtv, xc, yc, color);
	
	free(vectors[VCTR_D]);
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
