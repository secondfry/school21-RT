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

typedef struct s_pre_light
{
	t_light_params	params;
	t_vector_4		P;
	t_vector_4		N;
	t_vector_4		V;
	float			intensity;
}				t_pre_light;

void	process_pixel(t_rtv *rtv, short xc, short yc);

#endif
