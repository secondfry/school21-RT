#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "typedef_common.h"
# include "rtv.h"
# include "vector.h"
# include "color.h"
# include "intersection.h"
# include "matrix_utils.h"
# include "normal.h"
# include "raytrace_light.h"
# include "filter.h"

// FIXME(secondfry): unused
typedef struct s_pre_light
{
	t_light_params	params;
	t_vector_4		vec_p;
	t_vector_4		vec_n;
	t_vector_4		vec_v;
	double			intensity;
}				t_pre_light;

t_color	process_pixel(t_rtv *rtv, short xc, short yc);

#endif
