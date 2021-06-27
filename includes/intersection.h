#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "defines.h"
# include "intersection_plane.h"
# include "intersection_sphere.h"

t_intersection	intersection_closest(t_rtv *rtv, t_intersect_params *params);

#endif
