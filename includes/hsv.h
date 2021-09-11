#include "rtv.h"

#ifndef HSV_H
# define HSV_H

typedef struct s_hsv
{
	t_byte	h;
	t_byte	s;
	t_byte	v;
}				t_hsv;

t_hsv	*change_hue(t_hsv *hsv);
t_color	hsv_to_rgb(t_hsv hsv);
t_hsv	rgb_to_hsv(t_color *c);
t_byte	rgb_get_min(t_byte r, t_byte g, t_byte b);
t_byte	rgb_get_max(t_byte r, t_byte g, t_byte b);

#endif
