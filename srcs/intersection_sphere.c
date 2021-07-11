#include "intersection_sphere.h"

// https://www.gabrielgambetta.com/
// computer-graphics-from-scratch/04-shadows-and-reflections.html

static void	intersection_sphere(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx,
	float t[2]
)
{
	const t_intersection_sphere	data = {
		rtv->spheres[idx].vectors[VCTR_SPHERE_C],
		vector_sub(params->O, data.C),
		vector_dot(params->D, params->D),
		2 * vector_dot(params->D, data.CO),
		vector_dot(data.CO, data.CO) - rtv->spheres[idx].radius_squared,
		sqrtf(data.b * data.b - 4 * data.a * data.c)
	};

	if (data.sqrt < 0)
	{
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return ;
	}
	t[0] = (-1 * data.b + sqrtf(data.sqrt)) / (2 * data.a);
	t[1] = (-1 * data.b - sqrtf(data.sqrt)) / (2 * data.a);
}

t_intersection	intersection_sphere_closest(
	t_rtv *rtv,
	t_intersect_params *params
)
{
	float	t_closest;
	t_byte	idx;
	t_byte	i;
	float	t[2];

	t_closest = 1.0 / 0.0;
	idx = -1;
	i = 0;
	while (i < MAX_SPHERES)
	{
		if (!(rtv->spheres[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		intersection_sphere(rtv, params, i, t);
		if (t[0] > params->t_min && t[0] < params->t_max && t[0] < t_closest)
		{
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > params->t_min && t[1] < params->t_max && t[1] < t_closest)
		{
			t_closest = t[1];
			idx = i;
		}
		i++;
	}
	return ((t_intersection){t_closest, idx, ISPHERE});
}
