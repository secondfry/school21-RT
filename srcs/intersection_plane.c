#include "intersection_plane.h"

// https://www.scratchapixel.com/
// lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/
// ray-plane-and-ray-disk-intersection

// (C - P) dot N = 0
// O + D * t = P

// (C - (O + D * t)) dot N = 0
// (C - O - D * t) dot N = 0
// (C - O) dot N - t * D dot N = 0
// t = (C - O) dot N / D dot N

static float	intersection_plane(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx
)
{
	const t_vector_4	C = rtv->planes[idx].position;
	const t_vector_4	CO = vector_sub(C, params->O);
	const float			a = vector_dot(rtv->planes[idx].normal, CO);
	const float			b = vector_dot(rtv->planes[idx].normal, params->D);

	if (b < EPSILON && b > -1 * EPSILON)
	{
		return (1.0 / 0.0);
	}
	return (a / b);
}

t_intersection	intersection_plane_closest(
	t_rtv *rtv,
	t_intersect_params *params
)
{
	float	t_closest;
	t_byte	idx;
	t_byte	i;
	float	t;

	t_closest = 1.0 / 0.0;
	idx = -1;
	i = 0;
	while (i < MAX_PLANES)
	{
		if (!(rtv->planes[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		t = intersection_plane(rtv, params, i);
		if (t > params->t_min && t < params->t_max && t < t_closest)
		{
			t_closest = t;
			idx = i;
		}
		i++;
	}
	return ((t_intersection){t_closest, idx, IPLANE});
}
