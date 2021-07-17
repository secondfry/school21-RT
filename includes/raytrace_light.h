#ifndef RAYTRACE_LIGHT_H
# define RAYTRACE_LIGHT_H

# include "defines.h"
# include "vector.h"
# include "intersection.h"

float	light(\
	t_rtv *rtv, \
	const t_light_params *params \
);

#endif
