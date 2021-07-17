#ifndef INTERSECTION_CYLINDER_H
# define INTERSECTION_CYLINDER_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"
# include "intersection_common.h"

typedef struct s_intersection_cylinder
{
	t_vector_4	C;
	t_vector_4	CO;
	t_vector_4	CQ;
	t_vector_4	X;
	t_vector_4	Z;
	float		a;
	float		b;
	float		c;
	float		sqrt;
}				t_intersection_cylinder;

t_intersection	intersection_cylinder_closest( \
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
