#ifndef INTERSECTION_SPHERE_H
# define INTERSECTION_SPHERE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"

typedef struct s_intersection_sphere
{
	t_vector_4	C;
	t_vector_4	CO;
	float		a;
	float		b;
	float		c;
	float		sqrt;
}				t_intersection_sphere;

t_intersection	intersection_sphere_closest(t_rtv *rtv, t_intersect_params *params);

#endif
