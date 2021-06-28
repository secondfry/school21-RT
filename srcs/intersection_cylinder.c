#include "intersection_cylinder.h"

// https://math.stackexchange.com/questions/3248356/calculating-ray-cylinder-intersection-points/3248403#3248403

// t^2 = (r^2 - d^2) / b^2;

// xVec = cylinder direction cross D (ray direction)
// yVec = cylinder direction
// zVec = yVec cross xVec
// QP = (CO dot xVec) mult xVec

// d = QP dot xVec
// b = D dot zVec
// y = D dot yVec

// get t
// P = d * xVec + b * t * zVec + y * t * yVec

// then you just calculate T and R matrixes, multiply them, invert and apply to P
// or...

// https://stackoverflow.com/a/37793274

static void	intersection_cylinder(t_rtv *rtv, t_intersect_params *params, t_byte idx, float t[2])
{
	t_vector_4 C = rtv->cylinders[idx].vectors[VCTR_CYLINDER_C0];
	t_vector_4 CO = vector_sub(params->O, C);
	t_vector_4 CQ = vector_sub(rtv->cylinders[idx].vectors[VCTR_CYLINDER_C1], rtv->cylinders[idx].vectors[VCTR_CYLINDER_C0]);
    t_vector_4 X = vector_cross(CO, CQ);
    t_vector_4 Z = vector_cross(params->D, CQ);
    float   a = vector_dot(Z, Z);
    float   b = 2 * vector_dot(Z, X);
    float   c = vector_dot(X, X) - (rtv->cylinders[idx].radius_squared * vector_dot(CQ, CQ));
    float	sqrt;
    sqrt = sqrtf((b * b) - (4.0 * a * c));
    if (sqrt < 0) {
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return;
	}
    t[0] = (-1 * b - sqrt) / (2.0 * a);
    t[1] = (-1 * b + sqrt) / (2.0 * a);
}

t_intersection	intersection_cylinder_closest(t_rtv *rtv, t_intersect_params *params)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
	float t[2];

	for (t_byte i = 0; i < MAX_CYLINDERS; i++) {
		if (!(rtv->cylinders[i].traits & TRAIT_EXISTS))
			continue;
		intersection_cylinder(rtv, params, i, t);
		if (t[0] > params->t_min && t[0] < params->t_max && t[0] < t_closest) {
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > params->t_min && t[1] < params->t_max && t[1] < t_closest) {
			t_closest = t[1];
			idx = i;
		}
	}
	return ((t_intersection) { t_closest, idx, ICYLINDER });
}
