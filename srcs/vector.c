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
