#ifndef NORMAL_H
# define NORMAL_H

# include "defines.h"
# include "vector.h"

t_vector_4	find_normal(\
	t_rtv *rtv, \
	t_intersection *intr, \
	const t_light_params *params, \
	t_vector_4 P \
);

#endif
