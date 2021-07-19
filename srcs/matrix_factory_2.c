/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_factory_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:04:37 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/19 19:33:35 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_factory.h"

t_matrix_4	matrix_new_projection_ortho(
	double fov,
	double ratio,
	double near,
	double far
)
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
	ret[0] = 2 / width;
	ret[5] = 2 / height;
	ret[10] = -1 * (far + near) / (far - near);
	ret[14] = -1;
	ret[11] = -2 * far * near / (far - near);
	ret[15] = 0;
	return (ret);
}
