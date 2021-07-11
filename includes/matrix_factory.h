/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_factory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:07:08 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/06 21:47:02 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_FACTORY_H
# define MATRIX_FACTORY_H

# include <math.h>
# include "libft.h"
# include "defines.h"
# include "graceful.h"

t_matrix_4	matrix_new_identity(void);
t_matrix_4	matrix_new_translation(float x, float y, float z);
t_matrix_4	matrix_new_scale(float factor_x, float factor_y, float factor_z);
t_matrix_4	matrix_new_rotation(float angle_x, float angle_y, float angle_z);
t_matrix_4	matrix_new_projection(\
	float fov, \
	float ratio, \
	float near, \
	float far \
);
t_matrix_4	matrix_new_projection_ortho(\
	float fov, \
	float ratio, \
	float near, \
	float far \
);

#endif
