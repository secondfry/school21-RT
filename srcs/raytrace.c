#include "raytrace.h"

static float	light_one(
	t_rtv *rtv,
	const t_light_params *params,
	float cutoff,
	float light_intensity
)
{
	const t_vector_4		R = vector_new(0, 0, 0, 0);
	const t_intersection	res = intersection_closest(\
		rtv, &((t_intersect_params){params->P, params->L, EPSILON, cutoff}));
	float					dot;
	float					intensity;

	intensity = 0;
	if (res.distance != 1.0 / 0.0)
		return (intensity);
	dot = vector_dot(params->N, params->L);
	if (dot > 0)
		intensity += light_intensity * dot / vector_length(params->L);
	if (params->specular == -1)
		return (intensity);
	vector_set_by_value(&R, vector_sub(\
		vector_mult(params->N, 2 * vector_dot(params->N, params->L)), \
		params->L) \
	);
	dot = vector_dot(R, params->V);
	if (dot > 0)
		intensity += light_intensity * powf(\
			dot / vector_length(R) / vector_length(params->V), \
			params->specular \
		);
	return (intensity);
}

// NOTE(secondfry): should really optimize getting cutoff and vector math...
static float	light_point(
	t_rtv *rtv,
	const t_light_params *params
)
{
	const t_vector_4	L = vector_new(0, 0, 0, 0);
	float				intensity;
	t_byte				i;
	float				cutoff;

	intensity = 0;
	i = 0;
	while (i < MAX_PLIGHTS)
	{
		if (!(rtv->plights[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		vector_set_by_value(&L, \
			vector_sub(rtv->plights[i].position, params->P));
		cutoff = vector_length(L);
		vector_set_by_value(&params->L, vector_normalize(L));
		intensity += light_one(rtv, params, cutoff, rtv->plights[i].intensity);
		i++;
	}
	return (intensity);
}

static float	light_directional(
	t_rtv *rtv,
	const t_light_params *params
)
{
	float	intensity;
	t_byte	i;

	intensity = 0;
	i = 0;
	while (i < MAX_DLIGHTS)
	{
		if (!(rtv->dlights[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		vector_set_by_value(&params->L, rtv->dlights[i].direction);
		intensity += light_one(\
			rtv, \
			params, \
			1.0 / 0.0, \
			rtv->dlights[i].intensity \
		);
		i++;
	}
	return (intensity);
}

static float	light(
	t_rtv *rtv,
	const t_light_params *params
)
{
	float	intensity;

	intensity = rtv->ambient + \
		light_point(rtv, params) + \
		light_directional(rtv, params);
	return (intensity);
}

static t_light_params	get_light_params(t_rtv *rtv, t_intersection *intr)
{
	if (intr->type == ISPHERE)
		return ((t_light_params){\
			.C = rtv->spheres[intr->idx].vectors[VCTR_SPHERE_C], \
			.color = rtv->spheres[intr->idx].color, \
			.specular = rtv->spheres[intr->idx].specular \
		});
	if (intr->type == IPLANE)
		return ((t_light_params){\
			.C = rtv->planes[intr->idx].position, \
			.color = rtv->planes[intr->idx].color, \
			.specular = rtv->planes[intr->idx].specular \
		});
	if (intr->type == ICYLINDER)
		return ((t_light_params){\
			.C = rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0], \
			.color = rtv->cylinders[intr->idx].color, \
			.specular = rtv->cylinders[intr->idx].specular \
		});
	if (intr->type == ICONE)
		return ((t_light_params){\
			.C = rtv->cones[intr->idx].vectors[VCTR_CONE_C0], \
			.color = rtv->cones[intr->idx].color, \
			.specular = rtv->cones[intr->idx].specular \
		});
	return ((t_light_params){});
}

static t_color	pre_light(t_rtv *rtv, t_worker_data *data, t_intersection *intr)
{
	const t_light_params	params = get_light_params(rtv, intr);
	float					intensity;

	vector_set_by_value(&params.P, vector_add(\
		data->vectors[VCTR_O], \
		vector_mult(data->vectors[VCTR_D], intr->distance) \
	));
	vector_set_by_value(\
		&params.N, find_normal(rtv, intr, &params));
	vector_set_by_value(&params.V, vector_mult(data->vectors[VCTR_D], -1));
	intensity = light(rtv, &params);
	return (color_mult(params.color, intensity));
}

static t_color	raytrace(
	t_rtv *rtv,
	t_worker_data *data,
	float t_min,
	float t_max
)
{
	t_intersection	intr;

	intr = intersection_closest(\
		rtv, \
		&((t_intersect_params){\
			data->vectors[VCTR_O], \
			data->vectors[VCTR_D], \
			t_min, \
			t_max \
		}) \
	);
	if (intr.distance == 1.0 / 0.0)
		return (color_new(0, 0, 0));
	return (pre_light(rtv, data, &intr));
}

static void	canvas_to_screen(t_rtv *rtv, short xc, short yc, t_color color)
{
	t_ushort	xs;
	t_ushort	ys;

	xs = WIDTH / 2 + xc;
	ys = HEIGHT / 2 - yc;
	rtv->mlx->img_data[ys * rtv->mlx->size_line_int + xs] = color_to_int(color);
}

void	process_pixel(t_rtv *rtv, short xc, short yc)
{
	t_color				color;
	const t_vector_4	D = vector_normalize(matrix_on_vector(
		rtv->camera_rotation,
		(t_vector_4){(float) xc / WIDTH, (float) yc / HEIGHT, 1.f, 0}
	));
	t_worker_data		data;

	vector_set(data.vectors + VCTR_O, &rtv->camera_position);
	vector_set(data.vectors + VCTR_D, &D);
	data.floats[D_DOT_D] = vector_dot(\
		data.vectors[VCTR_D], \
		data.vectors[VCTR_D] \
	);
	color = raytrace(rtv, &data, 1.0f, 1.0 / 0.0);
	canvas_to_screen(rtv, xc, yc, color);
	free(color);
}
