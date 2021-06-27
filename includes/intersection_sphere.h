#ifndef INTERSECTION_SPHERE_H
# define INTERSECTION_SPHERE_H

# include <math.h>
# include "libft.h"
# include "vector.h"

typedef struct	s_intersection_sphere_closest
{
	float	distance;
	t_byte	sphere_idx;
}				t_intersection_sphere_closest;

t_intersection_sphere_closest	intersection_sphere_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max);

#endif
