#include "intersection_cone.h"

// lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

static void	intersection_cone(
	t_rtv *rtv,
	t_intersect_params *params,
	t_byte idx,
	float	t[2]
)
{
	const t_intersection_cone	data = {
		rtv->cones[idx].vectors[VCTR_CONE_C0],
		vector_sub(params->O, data.C),
		vector_normalize(
			vector_sub(
				rtv->cones[idx].vectors[VCTR_CONE_C1],
				rtv->cones[idx].vectors[VCTR_CONE_C0]
			)
		),
		vector_dot(vector_normalize(params->D), data.CQ),
		vector_dot(data.CO, data.CQ),
		vector_dot(vector_normalize(params->D), data.CO),
		vector_dot(data.CO, data.CO),
		rtv->cones[idx].cos2,
		data.DdotCQ * data.DdotCQ - data.cos2,
		2 * (data.DdotCQ * data.COdotCQ - data.DdotCO * data.cos2),
		data.COdotCQ * data.COdotCQ - data.COdotCO * data.cos2,
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

t_intersection	intersection_cone_closest(
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
	while (i < MAX_CONES)
	{
		if (!(rtv->cones[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		intersection_cone(rtv, params, i, t);
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
	return ((t_intersection){t_closest, idx, ICONE});
}
