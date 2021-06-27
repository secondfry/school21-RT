#ifndef INTERSECTION_PLANE_H
# define INTERSECTION_PLANE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"

t_intersection	intersection_plane_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max);

#endif
