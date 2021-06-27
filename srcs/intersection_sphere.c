#include "intersection_sphere.h"

static void	intersection_sphere(t_rtv *rtv, t_intersect_params *params, t_byte idx, float t[2])
{
	t_vector_4 C = rtv->spheres[idx].vectors[VCTR_C];
	t_vector_4 CO = vector_sub(params->O, C);
	float a = vector_dot(params->D, params->D);
	float b = 2 * vector_dot(params->D, CO);
	float c = vector_dot(CO, CO) - rtv->spheres[idx].radius_squared; // float is not enough here
	float sqrt = b * b - 4 * a * c;
	if (sqrt < 0) {
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return;
	}
	t[0] = (-1 * b + sqrtf(sqrt)) / (2 * a);
	t[1] = (-1 * b - sqrtf(sqrt)) / (2 * a);
}

t_intersection	intersection_sphere_closest(t_rtv *rtv, t_intersect_params *params)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
	float t[2];

	for (t_byte i = 0; i < MAX_SPHERES; i++) {
		if (!(rtv->spheres[i].traits & TRAIT_EXISTS))
			continue;
		intersection_sphere(rtv, params, i, t);
		if (t[0] > params->t_min && t[0] < params->t_max && t[0] < t_closest) {
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > params->t_min && t[1] < params->t_max && t[1] < t_closest) {
			t_closest = t[1];
			idx = i;
		}
	}
	return ((t_intersection) { t_closest, idx, ISPHERE });
}
