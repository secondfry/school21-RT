/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_perlin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:51:59 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 23:01:31 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace/raytrace_perlin.h"
#include <stdlib.h>

t_vector_2	g_perlin[PERLIN_SIZE * PERLIN_SIZE];

inline double	interpolate(double a0, double a1, double w)
{
	if (0.0 > w)
		return (a0);
	if (1.0 < w)
		return (a1);
	return ((a1 - a0) * (3.0 - w * 2.0) * w * w + a0);
}

void	init_perlin(void)
{
	size_t	i;

	i = 0;
	while (i < PERLIN_SIZE * PERLIN_SIZE)
	{
		g_perlin[i] = (t_vector_2){
			(double)rand() / RAND_MAX * 2 - 1,
			(double)rand() / RAND_MAX * 2 - 1
		};
		i++;
	}
}

inline double	dot_from_grid(int ix, int iy, double x, double y)
{
	const t_vector_2	gradient = g_perlin[iy * 16 + ix];
	const double		dx = x - (double)ix;
	const double		dy = y - (double)iy;

	return (dx * gradient.x + dy * gradient.y);
}

double	perlin(double x, double y)
{
	const int		xy[4] = {
		(int)x,
		xy[0] + 1,
		(int)y,
		xy[2] + 1,
	};
	const double	sx = x - (double)xy[0];
	const double	sy = y - (double)xy[2];

	return (interpolate(\
		interpolate(\
			dot_from_grid(xy[0], xy[2], x, y), \
			dot_from_grid(xy[1], xy[2], x, y), \
			sx \
		), \
		interpolate(\
			dot_from_grid(xy[0], xy[3], x, y), \
			dot_from_grid(xy[1], xy[3], x, y), \
			sx \
		), \
		sy \
	));
}
