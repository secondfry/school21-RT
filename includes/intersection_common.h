#ifndef INTERSECTION_COMMON_H
# define INTERSECTION_COMMON_H

# include "defines.h"

void	check_cropping_plane(\
	t_rtv *rtv, \
	t_vector_4 vec_o, \
	t_vector_4 vec_d, \
	double *distance \
);
void	check_intersection(\
	t_intersection *ret, \
	t_intersect_params *params, \
	double t, \
	t_byte i \
);

#endif
