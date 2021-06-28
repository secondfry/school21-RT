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
	// t_vector_4 C = rtv->cylinders[idx].position;
	// t_vector_4 CO = vector_sub(params->O, C);

	// t_vector_4 X = vector_normalize(vector_cross(rtv->cylinders[idx].normal, params->D));
	// t_vector_4 Y = vector_normalize(params->D);
	// t_vector_4 Z = vector_normalize(vector_cross(Y, X));
	// t_vector_4 QR = vector_mult(X, vector_dot(CO, X));

	// float d = vector_dot(QR, X);
	// float b = vector_dot(params->D, Z);
	// float y = vector_dot(params->D, Y);

	// float sqrt = (rtv->cylinders[idx].radius_squared - d * d) / b / b;
	// if (sqrt < 0) {
	// 	t[0] = 1.0 / 0.0;
	// 	t[1] = 1.0 / 0.0;
	// 	return;
	// }

	// float k = sqrtf(sqrt);
	// t_vector_4 P = vector_add(vector_add(vector_mult(X, d), vector_mult(Z, k * b)), vector_mult(Y, k * y));


	t_vector_4  pdp = vector_sub(rtv->cylinders[idx].normal, rtv->cylinders[idx].position);
	ft_memcpy((void*)&pdp, &((t_vector_4) { pdp.x, pdp.y, pdp.z, 0 }), sizeof(t_vector_4));
    t_vector_4  eyexpdp = vector_cross(vector_sub(params->O, rtv->cylinders[idx].position), pdp);
    t_vector_4  rdxpdp = vector_cross(params->D, pdp);
    float   a = vector_dot(rdxpdp, rdxpdp);
    float   b = 2 * vector_dot(rdxpdp, eyexpdp);
    float   c = vector_dot(eyexpdp, eyexpdp) - (rtv->cylinders[idx].radius_squared * vector_dot(pdp, pdp));
    float	delta;
    delta = sqrtf((b * b) - (4.0 * a * c));
    if (delta < 0) {
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return;
	}
    t[0] = (-b - (delta)) / (2.0 * a);
    t[1] = (-b + (delta)) / (2.0 * a);
	return;



	// t_vector_4 C = rtv->cylinders[idx].position;
	// t_vector_4 CO = vector_sub(params->O, C);

	// t_vector_4 X = vector_cross(CO, rtv->cylinders[idx].normal);
	// // t_vector_4 Y = vector_normalize(params->D);
	// // t_vector_4 Z = vector_normalize(vector_cross(Y, rtv->cylinders[idx].normal));
	// t_vector_4 Z = vector_cross(params->D, rtv->cylinders[idx].normal);

	// float a = vector_dot(Z, Z);
	// float b = 2 * vector_dot(Z, X);
	// float c = vector_dot(X, X) - rtv->cylinders[idx].radius_squared * vector_dot(CO, CO);

	// float sqrt = b * b - 4 * a * c;
	// if (sqrt < 0) {
	// 	t[0] = 1.0 / 0.0;
	// 	t[1] = 1.0 / 0.0;
	// 	return;
	// }

	// t[0] = (-1 * b + sqrtf(sqrt)) / (2 * a);
	// t[1] = (-1 * b - sqrtf(sqrt)) / (2 * a);
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
