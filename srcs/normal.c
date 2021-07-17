#include "normal.h"

static t_vector_4	find_normal_cone(
	t_rtv *rtv,
	t_intersection *intr,
	t_vector_4 P
)
{
	const t_vector_4	CP = vector_sub(\
		P, \
		rtv->cones[intr->idx].vectors[VCTR_CONE_C0] \
	);
	const t_vector_4	C0C1 = rtv->cones[intr->idx].vectors[VCTR_CONE_C0C1];
	const float			k = vector_length(CP) / rtv->cones[intr->idx].cos;
	const t_vector_4	CQ = vector_mult(C0C1, k);

	if (vector_dot(CP, C0C1) < 0)
		vector_set_by_value(&CQ, vector_mult(CQ, -1));
	return (vector_normalize(vector_sub(CP, CQ)));
}

static t_vector_4	find_normal_cylinder(
	t_rtv *rtv,
	t_intersection *intr,
	t_vector_4 P
)
{
	const t_vector_4	CP = vector_sub(\
		P, \
		rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0] \
	);
	const t_vector_4	C0C1 = \
		rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0C1];
	const float			k = vector_dot(CP, C0C1);
	const t_vector_4	CQ = vector_mult(C0C1, k);

	return (vector_normalize(vector_sub(CP, CQ)));
}

t_vector_4	find_normal(
	t_rtv *rtv,
	t_intersection *intr,
	const t_light_params *params
)
{
	if (intr->type == IPLANE)
		return (rtv->planes[intr->idx].normal);
	if (intr->type == ISPHERE)
		return (vector_normalize(vector_sub(params->P, params->C)));
	if (intr->type == ICONE)
		return (find_normal_cone(rtv, intr, params->P));
	if (intr->type == ICYLINDER)
		return (find_normal_cylinder(rtv, intr, params->P));
	return ((t_vector_4){0, 0, 0, 0});
}
