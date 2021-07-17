#include "raytrace_light.h"

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

float	light(
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
