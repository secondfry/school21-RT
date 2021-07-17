#ifndef INTERSECTION_CONE_H
# define INTERSECTION_CONE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"
# include "intersection_common.h"

typedef struct s_intersection_cone
{
	t_vector_4	C;
	t_vector_4	CO;
	t_vector_4	CQ;
	float		DdotCQ;
	float		COdotCQ;
	float		DdotCO;
	float		COdotCO;
	float		cos2;
	float		a;
	float		b;
	float		c;
	float		cubed;
	float		sqrt;
}				t_intersection_cone;

t_intersection	intersection_cone_closest(\
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
