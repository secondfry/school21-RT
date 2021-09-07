#include "normal.h"
#include "quaternion.h"
#include "matrix_utils.h"

static t_vector_4	find_normal_cone(
	t_rtv *rtv,
	t_intersection *intr,
	t_vector_4 P
)
{
	const t_vector_4	vec_cp = vector_sub(\
		P, \
		rtv->cones[intr->idx].vectors[VCTR_CONE_C0] \
	);
	const t_vector_4	vec_c0c1 = \
		rtv->cones[intr->idx].vectors[VCTR_CONE_C0C1];
	const double		k = vector_length(vec_cp) / rtv->cones[intr->idx].cos;
	const t_vector_4	vec_cq = vector_mult(vec_c0c1, k);

	if (vector_dot(vec_cp, vec_c0c1) < 0)
		vector_set_by_value(&vec_cq, vector_mult(vec_cq, -1));
	return (vector_normalize(vector_sub(vec_cp, vec_cq)));
}

static t_vector_4	find_normal_cylinder(
	t_rtv *rtv,
	t_intersection *intr,
	t_vector_4 P
)
{
	const t_vector_4	vec_cp = vector_sub(\
		P, \
		rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0] \
	);
	const t_vector_4	vec_c0c1 = \
		rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0C1];
	const double		k = vector_dot(vec_cp, vec_c0c1);
	const t_vector_4	vec_cq = vector_mult(vec_c0c1, k);

	return (vector_normalize(vector_sub(vec_cp, vec_cq)));
}

static t_vector_4	find_normal_sphere(
	t_rtv *rtv,
	t_intersection *intr,
	const t_light_params *params
)
{
	const t_sphere		this = rtv->spheres[intr->idx];
	const t_vector_4	vec_n = vector_normalize(\
		vector_sub(params->vec_p, params->vec_c));
	t_quaternion		rotator;
	t_matrix_4			matrix;

	if (!(this.traits & TRAIT_NORMAL_SIN))
		return (vec_n);
	rotator = quaternion_new(0, 0, \
		sin(100 * (params->vec_p.y - params->vec_c.y)));
	matrix = quaternion_to_matrix(rotator);
	vector_set_by_value(&vec_n, matrix_on_vector(matrix, vec_n));
	free(matrix);
	free(rotator);
	return (vec_n);
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
		return (find_normal_sphere(rtv, intr, params));
	if (intr->type == ICONE)
		return (find_normal_cone(rtv, intr, params->vec_p));
	if (intr->type == ICYLINDER)
		return (find_normal_cylinder(rtv, intr, params->vec_p));
	return ((t_vector_4){0, 0, 0, 0});
}
