#ifndef INTERSECTION_PLANE_H
# define INTERSECTION_PLANE_H

# include <math.h>
# include "libft.h"
# include "vector.h"

typedef struct	s_intersection_plane_closest
{
	float	distance;
	t_byte	plane_idx;
}				t_intersection_plane_closest;

t_intersection_plane_closest	intersection_plane_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max);

#endif
