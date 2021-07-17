/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 13:57:53 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/17 17:57:20 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vector_dot(t_vector_4 a, t_vector_4 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

float	vector_length(t_vector_4 a)
{
	return (sqrtf(vector_dot(a, a)));
}

t_vector_4	vector_normalize(t_vector_4 a)
{
	float	length;

	length = vector_length(a);
	return ((t_vector_4){
		a.x / length,
		a.y / length,
		a.z / length,
		a.w / length
	});
}

t_vector_4	vector_cross(t_vector_4 a, t_vector_4 b)
{
	return ((t_vector_4){
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
