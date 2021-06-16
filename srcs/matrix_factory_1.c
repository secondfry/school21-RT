/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_factory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 22:07:08 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/06 22:07:12 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_factory.h"

t_matrix_4	matrix_new_identity(void)
{
	t_matrix_4	ret;

	ret = (float *)ft_memalloc(sizeof(float) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = 1;
	ret[5] = 1;
	ret[10] = 1;
	ret[15] = 1;
	return (ret);
}

t_matrix_4	matrix_new_translation(float x, float y, float z)
{
	t_matrix_4	ret;

	ret = matrix_new_identity();
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[3] = x;
	ret[7] = y;
	ret[11] = z;
	return (ret);
}

t_matrix_4	matrix_new_scale(float factor_x, float factor_y, float factor_z)
{
	t_matrix_4	ret;

	ret = (float *)ft_memalloc(sizeof(float) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = factor_x;
	ret[5] = factor_y;
	ret[10] = factor_z;
	ret[15] = 1;
	return (ret);
}

t_matrix_4	matrix_new_rotation(float angle_x, float angle_y, float angle_z)
{
	t_matrix_4	ret;
	float		h[8];

	ret = (float *)ft_memalloc(sizeof(float) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	h[0] = cosf(angle_x);
	h[1] = sinf(angle_x);
	h[2] = cosf(angle_y);
	h[3] = sinf(angle_y);
	h[4] = cosf(angle_z);
	h[5] = sinf(angle_z);
	h[6] = h[0] * h[3];
	h[7] = h[1] * h[3];
	ret[0] = h[2] * h[4];
	ret[1] = -h[2] * h[5];
	ret[2] = h[3];
	ret[4] = h[7] * h[4] + h[0] * h[5];
	ret[5] = -h[7] * h[5] + h[0] * h[4];
	ret[6] = -h[1] * h[2];
	ret[8] = -h[6] * h[4] + h[1] * h[5];
	ret[9] = h[6] * h[5] + h[1] * h[4];
	ret[10] = h[0] * h[2];
	ret[15] = 1;
	return (ret);
}

t_matrix_4	matrix_new_projection(float fov, float ratio, float near, float far)
{
	t_matrix_4	ret;
	float		scale;
	float		width;
	float		height;

	scale = tanf(fov * M_PI_2F / 180) * near;
	width = 2 * ratio * scale;
	height = 2 * scale;
	ret = (float *)ft_memalloc(sizeof(float) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = 2 * near / width;
	ret[5] = 2 * near / height;
	ret[10] = -1 * (far + near) / (far - near);
	ret[14] = -1;
	ret[11] = -2 * far * near / (far - near);
	ret[15] = 0;
	return (ret);
}
