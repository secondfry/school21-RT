#ifndef INTERSECTION_SPHERE_H
# define INTERSECTION_SPHERE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"

t_intersection	intersection_sphere_closest(t_rtv *rtv, t_vector_4 O, t_vector_4 D, float t_min, float t_max);

#endif
