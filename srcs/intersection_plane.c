#include "intersection_plane.h"

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

static float	intersection_plane(t_rtv *rtv, t_vector_4 O, t_vector_4 D, t_byte idx)
{
	// (C - O) dot normal / D dot normal
	t_vector_4 C = rtv->planes[idx].position;
	float b = vector_dot(rtv->planes[idx].normal, D);

	if (b < EPSILON) {
		return 1.0 / 0.0;
	}

	t_vector_4 CO = vector_sub(C, O);
	float a = vector_dot(rtv->planes[idx].normal, CO);
	free(CO);
	return a / b;
}

t_intersection	intersection_plane_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
	float t;

	for (t_byte i = 0; i < MAX_PLANES; i++) {
		if (!(rtv->planes[i].traits & TRAIT_EXISTS))
			continue;
		t = intersection_plane(rtv, O, D, i);
		if (t > t_min && t < t_max && t < t_closest) {
			t_closest = t;
			idx = i;
		}
	}
	return ((t_intersection) { t_closest, idx, IPLANE });
}
