#ifndef INTERSECTION_CYLINDER_H
# define INTERSECTION_CYLINDER_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"
# include "intersection_common.h"

typedef struct s_intersection_cylinder
{
	t_vector_4	vec_c;
	t_vector_4	vec_co;
	t_vector_4	vec_cq;
	t_vector_4	vec_x;
	t_vector_4	vec_z;
	double		a;
	double		b;
	double		c;
	double		cubed;
	double		sqrt;
}				t_intersection_cylinder;

t_intersection	intersection_cylinder_closest( \
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
