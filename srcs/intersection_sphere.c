#include "intersection_sphere.h"

static void	intersection_sphere(t_rtv *rtv, t_vector_4 O, t_vector_4 D, t_byte idx, float t[2])
{
	t_vector_4 C = rtv->spheres[idx].position;
	t_vector_4 CO = vector_sub(O, C);
	float a = vector_dot(D, D);
	float b = 2 * vector_dot(D, CO);
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

t_intersection	intersection_sphere_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
	float t[2];

	for (t_byte i = 0; i < MAX_SPHERES; i++) {
		if (!(rtv->spheres[i].traits & TRAIT_EXISTS))
			continue;
		intersection_sphere(rtv, O, D, i, t);
		if (t[0] > t_min && t[0] < t_max && t[0] < t_closest) {
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > t_min && t[1] < t_max && t[1] < t_closest) {
			t_closest = t[1];
			idx = i;
		}
	}
	return ((t_intersection) { t_closest, idx, ISPHERE });
}