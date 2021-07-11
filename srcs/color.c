#include "color.h"

t_color	color_new(t_byte r, t_byte g, t_byte b)
{
	t_color	ret;

	ret = malloc(sizeof(t_byte) * 3);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[TCRED] = r;
	ret[TCGREEN] = g;
	ret[TCBLUE] = b;
	return (ret);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	ret;
	t_byte	colors[3];

	if (255 - a[TCRED] > b[TCRED])
		colors[TCRED] = 255;
	else
		colors[TCRED] = a[TCRED] + b[TCRED];
	if (255 - a[TCGREEN] > b[TCGREEN])
		colors[TCGREEN] = 255;
	else
		colors[TCGREEN] = a[TCGREEN] + b[TCGREEN];
	if (255 - a[TCBLUE] > b[TCBLUE])
		colors[TCBLUE] = 255;
	else
		colors[TCBLUE] = a[TCBLUE] + b[TCBLUE];
	ret = color_new(colors[TCRED], colors[TCGREEN], colors[TCBLUE]);
	return (ret);
}

t_color	color_mult(t_color a, float k)
{
	t_byte	colors[3];

	if (k < 0)
		return (color_new(0, 0, 0));
	if (255 / k < a[TCRED])
		colors[TCRED] = 255;
	else
		colors[TCRED] = a[TCRED] * k;
	if (255 / k < a[TCGREEN])
		colors[TCGREEN] = 255;
	else
		colors[TCGREEN] = a[TCGREEN] * k;
	if (255 / k < a[TCBLUE])
		colors[TCBLUE] = 255;
	else
		colors[TCBLUE] = a[TCBLUE] * k;
	return (color_new(colors[TCRED], colors[TCGREEN], colors[TCBLUE]));
}

int	color_to_int(t_color a)
{
	return ((a[TCRED] << 16) + (a[TCGREEN] << 8) + a[TCBLUE]);
}
