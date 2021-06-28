/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:57:53 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/06/28 21:06:09 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector_4	vector_new(float x, float y, float z, float w)
{
	return ((t_vector_4) { x, y, z, w });
}

float	vector_dot(t_vector_4 a, t_vector_4 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

t_vector_4	vector_sub(t_vector_4 a, t_vector_4 b)
{
	return vector_new(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

t_vector_4	vector_add(t_vector_4 a, t_vector_4 b)
{
	return vector_new(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

t_vector_4	vector_mult(t_vector_4 a, float k)
{
	return vector_new(a.x * k, a.y * k, a.z * k, a.w * k);
}

float	vector_length(t_vector_4 a)
{
	return sqrtf(vector_dot(a, a));
}

t_vector_4	vector_normalize(t_vector_4 a)
{
	float	length;

	length = vector_length(a);
	return ((t_vector_4) { a.x / length, a.y / length, a.z / length, a.w / length });
}

t_vector_4	vector_cross(t_vector_4 a, t_vector_4 b)
{
	return ((t_vector_4) {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0
	});
}

void	vector_set(t_vector_4 *dst, t_vector_4 *src)
{
	ft_memcpy((void *) dst, src, sizeof(t_vector_4));
}
