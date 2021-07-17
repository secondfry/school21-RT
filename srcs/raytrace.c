#include "raytrace.h"

static float	light_point(t_rtv *rtv, t_vector_4 P, t_vector_4 N, t_vector_4 V, float specular)
{
	float		intensity;
	float		dot;

	intensity = 0;
	for (t_byte i = 0; i < MAX_PLIGHTS; i++) {
		if (!(rtv->plights[i].traits & TRAIT_EXISTS))
			continue ;
		t_vector_4 L = vector_sub(rtv->plights[i].position, P);
		t_intersection res = intersection_closest(rtv, &((t_intersect_params) { P, L, EPSILON, 1.f }));
		if (res.distance != 1.0 / 0.0)
			continue ;
		dot = vector_dot(N, L);
		if (dot > 0) {
			float delta = rtv->plights[i].intensity *
				dot / vector_length(L);
			intensity += delta;
		}
		if (specular == -1)
			continue ;
		t_vector_4 R = vector_sub(vector_mult(N, 2 * vector_dot(N, L)), L);
		dot = vector_dot(R, V);
		if (dot > 0) {
			float delta = rtv->plights[i].intensity *
				powf(dot / vector_length(R) / vector_length(V), specular);
			intensity += delta;
		}
	}
	return (intensity);
}

static float	light_directional(t_rtv *rtv, t_vector_4 P, t_vector_4 N, t_vector_4 V, float specular)
{
	float		intensity;
	float		dot;

	intensity = 0;
	for (t_byte i = 0; i < MAX_DLIGHTS; i++) {
		if (!(rtv->dlights[i].traits & TRAIT_EXISTS))
			continue;
		t_vector_4 L = rtv->dlights[i].direction;
		t_intersection res = intersection_closest(rtv, &((t_intersect_params) { P, L, EPSILON, 1.0 / 0.0 }));
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

typedef struct	s_light_params
{
	t_vector_4	C;
	t_color		color;
	float		specular;
}				t_light_params;

static t_light_params get_light_params(t_rtv *rtv, t_intersection *intr)
{
	if (intr->type == ISPHERE)
		return ((t_light_params) {
			rtv->spheres[intr->idx].vectors[VCTR_SPHERE_C],
			rtv->spheres[intr->idx].color,
			rtv->spheres[intr->idx].specular
		});
	if (intr->type == IPLANE)
		return ((t_light_params) {
			rtv->planes[intr->idx].position,
			rtv->planes[intr->idx].color,
			rtv->planes[intr->idx].specular
		});
	if (intr->type == ICYLINDER)
		return ((t_light_params) {
			rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0],
			rtv->cylinders[intr->idx].color,
			rtv->cylinders[intr->idx].specular
		});
	if (intr->type == ICONE)
		return ((t_light_params) {
			rtv->cones[intr->idx].vectors[VCTR_CONE_C0],
			rtv->cones[intr->idx].color,
			rtv->cones[intr->idx].specular
		});
	return ((t_light_params) {});
}

static t_vector_4 find_normal(t_rtv *rtv, t_intersection *intr, const t_light_params *params, t_vector_4 P)
{
	if (intr->type == IPLANE)
		return (rtv->planes[intr->idx].normal);
	if (intr->type == ISPHERE)
		return (vector_sub(P, params->C));
	if (intr->type == ICONE)
	{
		t_vector_4 CP = vector_normalize(vector_sub(P, rtv->cones[intr->idx].vectors[VCTR_CONE_C0]));
		t_vector_4 C1C0 = vector_normalize(vector_sub(rtv->cones[intr->idx].vectors[VCTR_CONE_C1], rtv->cones[intr->idx].vectors[VCTR_CONE_C0]));
		float k = vector_dot(CP, C1C0);
		t_vector_4 Q = vector_mult(C1C0, k);
		return (vector_normalize(vector_sub(C1C0, Q)));
	}

	if (intr->type == ICYLINDER)
	{
		t_vector_4 CP = vector_normalize(vector_sub(P, rtv->cones[intr->idx].vectors[VCTR_CONE_C0]));
		t_vector_4 C1C0 = vector_normalize(vector_sub(rtv->cones[intr->idx].vectors[VCTR_CONE_C1], rtv->cones[intr->idx].vectors[VCTR_CONE_C0]));
		float k = vector_dot(CP, C1C0);
		t_vector_4 Q = vector_mult(C1C0, k);
		return (vector_normalize(vector_sub(C1C0, Q)));
	}

	return ((t_vector_4) {0, 0, 0, 0});
}

static t_color pre_light(t_rtv *rtv, t_worker_data *data, t_intersection *intr)
{
	const t_light_params params = get_light_params(rtv, intr);
	const t_vector_4 P = vector_add(data->vectors[VCTR_O], vector_mult(data->vectors[VCTR_D], intr->distance));
	const t_vector_4 N = find_normal(rtv, intr, &params, P);
	const t_vector_4 NN = vector_normalize(N);
	const t_vector_4 V = vector_mult(data->vectors[VCTR_D], -1);
	float intensity = light(rtv, P, NN, V, params.specular);
	return color_mult(params.color, intensity);
}

static t_color	raytrace(t_rtv *rtv, t_worker_data *data, float t_min, float t_max)
{
	t_intersection	intr;

	intr = intersection_closest(rtv, &((t_intersect_params) { data->vectors[VCTR_O], data->vectors[VCTR_D], t_min, t_max }));
	if (intr.distance == 1.0 / 0.0)
		return color_new(0, 0, 0);
	return (pre_light(rtv, data, &intr));
}

static void canvas_to_screen(t_rtv *rtv, short xc, short yc, t_color color)
{
	t_ushort	xs;
	t_ushort	ys;

	xs = WIDTH / 2 + xc;
	ys = HEIGHT / 2 - yc;
	rtv->mlx->img_data[ys * rtv->mlx->size_line_int + xs] = color_to_int(color);
}

void	process_pixel(t_rtv *rtv, short xc, short yc)
{
	t_color 			color;
	const t_vector_4	D = matrix_on_vector(rtv->camera_rotation, (t_vector_4) { (float) xc / WIDTH, (float) yc / HEIGHT, 1.f, 0 });
	t_worker_data		data;

	vector_set(data.vectors + VCTR_O, &rtv->camera_position);
	vector_set(data.vectors + VCTR_D, &D);
	data.floats[D_DOT_D] = vector_dot(data.vectors[VCTR_D], data.vectors[VCTR_D]);
	color = raytrace(rtv, &data, 1.0f, 1.0 / 0.0);
	canvas_to_screen(rtv, xc, yc, color);
	free(color);
}
