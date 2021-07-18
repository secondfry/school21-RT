#ifndef TYPEDEF_COMMON_H
# define TYPEDEF_COMMON_H

# include "libft.h"

typedef const struct s_vector_4
{
	float	x;
	float	y;
	float	z;
	float	w;
}						t_vector_4;

# define TCRED		0
# define TCGREEN	1
# define TCBLUE		2

typedef struct s_color
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
}				t_color;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	size_t		size_line_int;
	size_t		size_line_char;
}				t_mlx;

typedef float			*t_matrix_4;
typedef float			*t_quaterion;
typedef const float		*t_const_matrix_4;
typedef const float		*t_const_quaterion;

#endif
