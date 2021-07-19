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
	double		DdotCQ;
	double		COdotCQ;
	double		DdotCO;
	double		COdotCO;
	double		cos2;
	double		a;
	double		b;
	double		c;
	double		cubed;
	double		sqrt;
}				t_intersection_cone;

t_intersection	intersection_cone_closest(\
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
