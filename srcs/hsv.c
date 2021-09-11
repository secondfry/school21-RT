#include "hsv.h"

t_byte	rgb_get_max(t_byte r, t_byte g, t_byte b)
{
	t_byte	max;

	if (r > g)
		max = r;
	else
		max = g;
	if (b > max)
		return (b);
	return (max);
}

t_byte	rgb_get_min(t_byte r, t_byte g, t_byte b)
{
	t_byte	min;

	if (r < g)
		min = r;
	else
		min = g;
	if (b < min)
		return (b);
	return (min);
}

t_hsv	rgb_to_hsv(t_color *c)
{
	t_hsv	hsv;
	t_byte	rgb_min;
	t_byte	rgb_max;

	rgb_min = rgb_get_min(c->red, c->green, c->blue);
	rgb_max = rgb_get_max(c->red, c->green, c->blue);
	hsv.v = rgb_max;
	if (hsv.v == 0)
		return ((t_hsv){0, 0, 0});
	hsv.s = 255 * (long)(rgb_max - rgb_min) / hsv.v;
	if (hsv.s == 0)
		return ((t_hsv){0, 0, hsv.v});
	if (rgb_max == c->red)
		hsv.h = 0 + 43 * (c->green - c->blue) / (rgb_max - rgb_min);
	else if (rgb_max == c->green)
		hsv.h = 85 + 43 * (c->blue - c->red) / (rgb_max - rgb_min);
	else
		hsv.h = 171 + 43 * (c->red - c->green) / (rgb_max - rgb_min);
	return (hsv);
}

t_color	hsv_to_rgb(t_hsv hsv)
{
	t_byte	region;
	t_byte	remainder;
	t_byte	p;
	t_byte	q;
	t_byte	t;

	if (hsv.s == 0)
		return ((t_color){hsv.v, hsv.v, hsv.v});
	region = hsv.h / 43;
	remainder = (hsv.h - (region * 43)) * 6;
	p = (hsv.v * (255 - hsv.s)) >> 8;
	q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
	t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
		return ((t_color){hsv.v, t, p});
	if (region == 1)
		return ((t_color){q, hsv.v, p});
	if (region == 2)
		return ((t_color){p, hsv.v, t});
	if (region == 3)
		return ((t_color){p, q, hsv.v});
	if (region == 4)
		return ((t_color){t, p, hsv.v});
	return ((t_color){hsv.v, p, q});
}

t_hsv	*change_hue(t_hsv *hsv)
{
	if (0 <= hsv->h && hsv->h < 22)
		hsv->h = 0;
	if (22 <= hsv->h && hsv->h < 42)
		hsv->h = 30;
	if (42 <= hsv->h && hsv->h < 64)
		hsv->h = 50;
	if (64 <= hsv->h && hsv->h < 106)
		hsv->h = 80;
	if (106 <= hsv->h && hsv->h < 191)
		hsv->h = 157;
	if (191 <= hsv->h && hsv->h <= 255)
		hsv->h = 222;
	return (hsv);
}
