#ifndef FILTER_H
# define FILTER_H

# include "color.h"

# define GRAYSCALE 1
# define SEPIA 2
# define INVERSION 3
# define CARTOON 4

t_color	apply_filter(t_color color, t_byte filter_code);
t_color	grayscale(t_color color);
t_color	sepia(t_color color);
t_color	cartoon(t_color color);

#endif
