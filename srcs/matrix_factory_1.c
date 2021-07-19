/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_factory_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 22:07:08 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/19 19:34:45 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_factory.h"

t_matrix_4	matrix_new_identity(void)
{
	t_matrix_4	ret;

	ret = (double *)ft_memalloc(sizeof(double) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = 1;
	ret[5] = 1;
	ret[10] = 1;
	ret[15] = 1;
	return (ret);
}

t_matrix_4	matrix_new_translation(double x, double y, double z)
{
	t_matrix_4	ret;

	ret = matrix_new_identity();
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[3] = x;
	ret[7] = y;
	ret[11] = z;
	return (ret);
}

t_matrix_4	matrix_new_scale(double factor_x, double factor_y, double factor_z)
{
	t_matrix_4	ret;

	ret = (double *)ft_memalloc(sizeof(double) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = factor_x;
	ret[5] = factor_y;
	ret[10] = factor_z;
	ret[15] = 1;
	return (ret);
}

t_matrix_4	matrix_new_rotation(double angle_x, double angle_y, double angle_z)
{
	t_matrix_4	ret;
	double		h[8];

	ret = (double *)ft_memalloc(sizeof(double) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	h[0] = cos(angle_x);
	h[1] = sin(angle_x);
	h[2] = cos(angle_y);
	h[3] = sin(angle_y);
	h[4] = cos(angle_z);
	h[5] = sin(angle_z);
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

t_matrix_4	matrix_new_projection(double fov, double ratio, double near, double far)
{
	t_matrix_4	ret;
	double		scale;
	double		width;
	double		height;

	scale = tanf(fov * M_PI_2F / 180) * near;
	width = 2 * ratio * scale;
	height = 2 * scale;
	ret = (double *)ft_memalloc(sizeof(double) * 16);
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret[0] = 2 * near / width;
	ret[5] = 2 * near / height;
	ret[10] = -1 * (far + near) / (far - near);
	ret[14] = -1;
	ret[11] = -2 * far * near / (far - near);
	ret[15] = 0;
	return (ret);
}
