#include "intersection_cylinder.h"

// https://math.stackexchange.com/a/3248403

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

// then you calculate T and R matrixes, multiply them, invert and apply to P
// or...

// https://stackoverflow.com/a/37793274

static void	intersection_cylinder(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx,
	float t[2]
)
{
	const t_intersection_cylinder	data = {
		rtv->cylinders[idx].vectors[VCTR_CYLINDER_C0],
		vector_sub(params->O, data.C),
		rtv->cylinders[idx].vectors[VCTR_CYLINDER_C0C1],
		vector_cross(data.CO, data.CQ),
		vector_cross(params->D, data.CQ),
		vector_dot(data.Z, data.Z),
		2 * vector_dot(data.Z, data.X),
		vector_dot(data.X, data.X) \
			- (rtv->cylinders[idx].radius2 * vector_dot(data.CQ, data.CQ)),
		sqrtf((data.b * data.b) - (4.0 * data.a * data.c))
	};

	if (data.sqrt < 0)
	{
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return ;
	}
	t[0] = (-1 * data.b - data.sqrt) / (2.0 * data.a);
	t[1] = (-1 * data.b + data.sqrt) / (2.0 * data.a);
}

t_intersection	intersection_cylinder_closest(
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
	while (i < MAX_CYLINDERS)
	{
		if (!(rtv->cylinders[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		intersection_cylinder(rtv, params, i, t);
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
	return ((t_intersection){t_closest, idx, ICYLINDER});
}
