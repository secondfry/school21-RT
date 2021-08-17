#ifndef TYPEDEF_COMMON_H
# define TYPEDEF_COMMON_H

# include "libft.h"

# define BUFFER_SIZE 1048576

typedef const struct s_vector_4
{
	double	x;
	double	y;
	double	z;
	double	w;
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

typedef double			*t_matrix_4;
typedef double			*t_quaterion;
typedef const double	*t_const_matrix_4;
typedef const double	*t_const_quaterion;

#endif
