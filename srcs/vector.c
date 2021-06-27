/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:57:53 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/06 22:09:01 by oadhesiv         ###   ########.fr       */
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
