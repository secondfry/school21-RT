#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "typedef_common.h"
# include "rtv.h"
# include "vector.h"
# include "color.h"
# include "intersection.h"
# include "matrix_utils.h"

void	process_pixel(t_rtv *rtv, short xc, short yc);

#endif
