#include "intersection_cone.h"

// https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

static void	intersection_cone(t_rtv *rtv, t_intersect_params *params, t_byte idx, float t[2])
{
	t_vector_4 C = rtv->cones[idx].vectors[VCTR_CONE_C0];
	t_vector_4 CO = vector_sub(params->O, C);
	t_vector_4 CQ = vector_normalize(vector_sub(rtv->cones[idx].vectors[VCTR_CONE_C1], rtv->cones[idx].vectors[VCTR_CONE_C0]));
	float DdotCQ = vector_dot(vector_normalize(params->D), CQ);
	float COdotCQ = vector_dot(CO, CQ);
	float DdotCO = vector_dot(vector_normalize(params->D), CO);
	float COdotCO = vector_dot(CO, CO);
	float cos = cosf(rtv->cones[idx].angle);
	float cos2 = cos * cos;
    float a = DdotCQ * DdotCQ - cos2;
    float b = 2 * (DdotCQ * COdotCQ - DdotCO * cos2);
    float c = COdotCQ * COdotCQ - COdotCO * cos2;
    float sqrt;
    sqrt = sqrtf((b * b) - (4.0 * a * c));
    if (sqrt < 0) {
		t[0] = 1.0 / 0.0;
		t[1] = 1.0 / 0.0;
		return;
	}
    t[0] = (-1 * b - sqrt) / (2.0 * a);
    t[1] = (-1 * b + sqrt) / (2.0 * a);
}

t_intersection	intersection_cone_closest(t_rtv *rtv, t_intersect_params *params)
{
	float t_closest = 1.0 / 0.0;
	t_byte idx = -1;
	float t[2];

	for (t_byte i = 0; i < MAX_CONES; i++) {
		if (!(rtv->cones[i].traits & TRAIT_EXISTS))
			continue;
		intersection_cone(rtv, params, i, t);
		if (t[0] > params->t_min && t[0] < params->t_max && t[0] < t_closest) {
			t_closest = t[0];
			idx = i;
		}
		if (t[1] > params->t_min && t[1] < params->t_max && t[1] < t_closest) {
			t_closest = t[1];
			idx = i;
		}
	}
	return ((t_intersection) { t_closest, idx, ICONE });
}
