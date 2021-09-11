#include "filter.h"
#include "hsv.h"

t_color	cartoon(t_color color)
{
	t_hsv	hsv;

	hsv = rgb_to_hsv(&color);
	change_hue(&hsv);
	hsv.v = (hsv.v / 32) * 32;
	return (hsv_to_rgb((t_hsv){hsv.h, hsv.s, hsv.v}));
}

t_color	sepia(t_color color)
{
	float	sepia_red;
	float	sepia_green;
	float	sepia_blue;

	sepia_red = .393 * color.red + .769 * color.green + .189 * color.blue;
	sepia_green = .349 * color.red + .686 * color.green + .168 * color.blue;
	sepia_blue = .272 * color.red + .534 * color.green + .131 * color.blue;
	if (sepia_red > 255)
		sepia_red = 255;
	if (sepia_green > 255)
		sepia_green = 255;
	if (sepia_blue > 255)
		sepia_blue = 255;
	color.red = sepia_red;
	color.green = sepia_green;
	color.blue = sepia_blue;
	return (color);
}

t_color	grayscale(t_color color)
{
	t_byte	gray;

	gray = (rgb_get_max(color.red, color.green, color.blue)
			+ rgb_get_min(color.red, color.green, color.blue)) / 2;
	color.red = gray;
	color.green = gray;
	color.blue = gray;
	return (color);
}

t_color	apply_filter(t_color color, t_byte filter_code)
{
	if (filter_code == SEPIA)
		return (sepia(color));
	if (filter_code == GRAYSCALE)
		return (grayscale(color));
	if (filter_code == INVERSION)
		return ((t_color){255 - color.red, 255 - color.green,
			255 - color.blue});
	if (filter_code == CARTOON)
		return (cartoon(color));
	return (color);
}
