#include "intersection_plane.h"

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

// (C - P) dot N = 0
// O + D * t = P

// (C - (O + D * t)) dot N = 0
// (C - O - D * t) dot N = 0
// (C - O) dot N - t * D dot N = 0
// t = (C - O) dot N / D dot N

static float	intersection_plane(t_rtv *rtv, t_intersect_params *params, t_byte idx)
{
	// (C - O) dot normal / D dot normal
	t_vector_4 C = rtv->planes[idx].position;
	float b = vector_dot(rtv->planes[idx].normal, params->D);

	// if (b < EPSILON && b > -1 * EPSILON) {
	// 	return 1.0 / 0.0;
	// }

	t_vector_4 CO = vector_sub(C, params->O);
	float a = vector_dot(rtv->planes[idx].normal, CO);
	return a / b;
}

t_intersection	intersection_plane_closest(t_rtv *rtv, t_intersect_params *params)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
	float t;

	for (t_byte i = 0; i < MAX_PLANES; i++) {
		if (!(rtv->planes[i].traits & TRAIT_EXISTS))
			continue;
		t = intersection_plane(rtv, params, i);
		if (t > params->t_min && t < params->t_max && t < t_closest) {
			t_closest = t;
			idx = i;
		}
	}
	return ((t_intersection) { t_closest, idx, IPLANE });
}
