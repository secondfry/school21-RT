#ifndef QUATERNION_H
# define QUATERNION_H

# include <math.h>
# include "libft.h"
# include "defines.h"
# include "graceful.h"

t_quaterion	quaternion_new(double angle_x, double angle_y, double angle_z);
t_matrix_4	quaternion_to_matrix(t_const_quaterion self);

#endif
