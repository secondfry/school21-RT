#ifndef TYPEDEF_COMMON_H
# define TYPEDEF_COMMON_H

# include "libft.h"

typedef const struct s_vector_4
{
	double	x;
	double	y;
	double	z;
	double	w;
}						t_vector_4;

typedef struct s_color
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
}				t_color;

typedef double			*t_matrix_4;
typedef double			*t_quaternion;
typedef const double	*t_const_matrix_4;
typedef const double	*t_const_quaternion;

#endif
