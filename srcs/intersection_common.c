#include "intersection_common.h"

void	check_intersection(
	t_intersection *ret,
	t_intersect_params *params,
	float t,
	t_byte i
)
{
	if (t > params->t_min && t < params->t_max && t < ret->distance)
	{
		ret->distance = t;
		ret->idx = i;
	}
}
