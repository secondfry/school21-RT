#ifndef COLOR_H
# define COLOR_H

# include "defines.h"
# include "graceful.h"

int		color_to_int(t_color a);
t_color	*color_mult(t_color *a, float k);
t_color	*color_zero(t_color *a);
t_color	*color_add(t_color *a, t_color *b);
t_color	*color_new(t_color *c, t_byte r, t_byte g, t_byte b);

#endif
