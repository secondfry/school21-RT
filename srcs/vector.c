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
	t_vector_4	ret;

	ret = (float *)ft_memalloc(sizeof(float) * 4);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = x;
	ret[1] = y;
	ret[2] = z;
	ret[3] = w;
	return (ret);
}

float	dot(t_vector_4 a, t_vector_4 b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
}

t_vector_4	vector_sub(t_vector_4 a, t_vector_4 b)
{
	return vector_new(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
}
