#include "color.h"

t_color	*color_new(t_color *c, t_byte r, t_byte g, t_byte b)
{
	c->red = r;
	c->green = g;
	c->blue = b;
	return (c);
}

t_color	*color_add(t_color *a, t_color *b)
{
	t_color	ret;

	if (255 - a->red > b->red)
		ret.red = 255;
	else
		ret.red = a->red + b->red;
	if (255 - a->green > b->green)
		ret.green = 255;
	else
		ret.green = a->green + b->green;
	if (255 - a->blue > b->blue)
		ret.blue = 255;
	else
		ret.blue = a->blue + b->blue;
	*a = ret;
	return (a);
}

t_color	*color_zero(t_color *a)
{
	a->red = 0;
	a->green = 0;
	a->blue = 0;
	return (a);
}

t_color	*color_mult(t_color *a, float k)
{
	t_color	ret;

	if (k < 0)
		return (color_zero(&ret));
	if (255 / k < a->red)
		ret.red = 255;
	else
		ret.red = a->red * k;
	if (255 / k < a->green)
		ret.green = 255;
	else
		ret.green = a->green * k;
	if (255 / k < a->blue)
		ret.blue = 255;
	else
		ret.blue = a->blue * k;
	*a = ret;
	return (a);
}

int	color_to_int(t_color *a)
{
	return ((a->red << 16) + (a->green << 8) + a->blue);
}
