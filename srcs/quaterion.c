/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaterion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 22:08:38 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/06 22:08:58 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaterion.h"

/*
** http://www.opengl-tutorial.org/assets/faq_quaternions/index.html
*/

t_quaterion	quaternion_new(float angle_x, float angle_y, float angle_z)
{
	t_quaterion	ret;
	float		h[8];

	h[7] = sinf(angle_x * 0.5F);
	h[6] = cosf(angle_x * 0.5F);
	h[5] = sinf(angle_y * 0.5F);
	h[4] = cosf(angle_y * 0.5F);
	h[3] = sinf(angle_z * 0.5F);
	h[2] = cosf(angle_z * 0.5F);
	h[1] = h[6] * h[4];
	h[0] = h[7] * h[5];
	ret = (float *)ft_memalloc(sizeof(float) * 4);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = h[3] * h[1] - h[2] * h[0];
	ret[1] = h[2] * h[7] * h[4] + h[3] * h[6] * h[5];
	ret[2] = h[2] * h[6] * h[5] - h[3] * h[7] * h[4];
	ret[3] = h[2] * h[1] + h[3] * h[0];
	return (ret);
}

t_matrix_4	quaternion_to_matrix(t_const_quaterion self)
{
	t_matrix_4	ret;
	float		h[9];

	h[8] = self[0] * self[0];
	h[7] = self[0] * self[1];
	h[6] = self[0] * self[2];
	h[5] = self[0] * self[3];
	h[4] = self[1] * self[1];
	h[3] = self[1] * self[2];
	h[2] = self[1] * self[3];
	h[1] = self[2] * self[2];
	h[0] = self[2] * self[3];
	ret = (float *)ft_memalloc(sizeof(float) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = 1 - 2 * (h[4] + h[1]);
	ret[4] = 2 * (h[7] - h[0]);
	ret[8] = 2 * (h[6] + h[2]);
	ret[1] = 2 * (h[7] + h[0]);
	ret[5] = 1 - 2 * (h[8] + h[1]);
	ret[9] = 2 * (h[3] - h[5]);
	ret[2] = 2 * (h[6] - h[2]);
	ret[6] = 2 * (h[3] + h[5]);
	ret[10] = 1 - 2 * (h[8] + h[4]);
	ret[15] = 1;
	return (ret);
}
