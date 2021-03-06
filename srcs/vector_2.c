/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:32:36 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:32:38 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector_4	vector_new(double x, double y, double z, double w)
{
	return ((t_vector_4){x, y, z, w});
}

t_vector_4	vector_sub(t_vector_4 a, t_vector_4 b)
{
	return ((t_vector_4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w});
}

t_vector_4	vector_add(t_vector_4 a, t_vector_4 b)
{
	return ((t_vector_4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}

t_vector_4	vector_mult(t_vector_4 a, double k)
{
	return ((t_vector_4){a.x * k, a.y * k, a.z * k, a.w * k});
}

void	vector_set_by_value(t_vector_4 *dst, t_vector_4 src)
{
	ft_memcpy((void *) dst, &src, sizeof(t_vector_4));
}
