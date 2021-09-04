#include "raytrace_light.h"

static double	light_one(
	t_rtv *rtv,
	const t_light_params *params,
	double cutoff,
	double light_intensity
)
{
	const t_vector_4		vec_r = vector_new(0, 0, 0, 0);
	const t_intersection	res = intersection_closest(rtv, \
		&((t_intersect_params){params->vec_p, params->vec_l, EPSILON, cutoff}));
	double					dot;
	double					intensity;

	intensity = 0;
	if (res.distance != 1.0 / 0.0)
		return (intensity);
	dot = vector_dot(params->vec_n, params->vec_l);
	if (dot > 0)
		intensity += light_intensity * dot / vector_length(params->vec_l);
	if (params->specular < 0)
		return (intensity);
	vector_set_by_value(&vec_r, vector_sub(vector_mult(params->vec_n, \
		2 * vector_dot(params->vec_n, params->vec_l)), params->vec_l));
	dot = vector_dot(vec_r, params->vec_v);
	if (dot > 0)
		intensity += light_intensity * powf(\
			dot / vector_length(vec_r) / vector_length(params->vec_v), \
			params->specular \
		);
	return (intensity);
}

// NOTE(secondfry): should really optimize getting cutoff and vector math...
static double	light_point(
	t_rtv *rtv,
	const t_light_params *params
)
{
	const t_vector_4	vec_l = vector_new(0, 0, 0, 0);
	double				intensity;
	t_byte				i;
	double				cutoff;

	intensity = 0;
	i = 0;
	while (i < MAX_PLIGHTS)
	{
		if (!(rtv->plights[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		vector_set_by_value(&vec_l, \
			vector_sub(rtv->plights[i].position, params->vec_p));
		cutoff = vector_length(vec_l) + EPSILON;
		vector_set_by_value(&params->vec_l, vector_normalize(vec_l));
		intensity += light_one(rtv, params, cutoff, rtv->plights[i].intensity);
		i++;
	}
	return (intensity);
}

static double	light_directional(
	t_rtv *rtv,
	const t_light_params *params
)
{
	double	intensity;
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
		vector_set_by_value(&params->vec_l, rtv->dlights[i].direction);
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

double	light(
	t_rtv *rtv,
	const t_light_params *params
)
{
	double	intensity;

	intensity = rtv->ambient + \
		light_point(rtv, params) + \
		light_directional(rtv, params);
	return (intensity);
}
