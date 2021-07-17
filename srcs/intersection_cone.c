#include "intersection_cone.h"

// https://lousodrome.net/
// blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

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
		rtv->cones[idx].vectors[VCTR_CONE_C0C1],
		vector_dot(params->D, data.CQ),
		vector_dot(data.CO, data.CQ),
		vector_dot(params->D, data.CO),
		vector_dot(data.CO, data.CO),
		rtv->cones[idx].cos2,
		data.DdotCQ * data.DdotCQ - data.cos2,
		2 * (data.DdotCQ * data.COdotCQ - data.DdotCO * data.cos2),
		data.COdotCQ * data.COdotCQ - data.COdotCO * data.cos2,
		(data.b * data.b) - (4.0 * data.a * data.c),
		sqrtf(data.cubed)
	};

	if (data.cubed < 0)
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
	t_intersection	ret;
	t_byte			i;
	float			t[2];

	ret.distance = 1.0 / 0.0;
	ret.idx = -1;
	ret.type = ICONE;
	i = 0;
	while (i < MAX_CONES)
	{
		if (!(rtv->cones[i].traits & TRAIT_EXISTS))
		{
			i++;
			continue ;
		}
		intersection_cone(rtv, params, i, t);
		check_intersection(&ret, params, t[0], i);
		check_intersection(&ret, params, t[1], i);
		i++;
	}
	return (ret);
}
