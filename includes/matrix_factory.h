/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_factory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:07:08 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/19 19:33:35 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_FACTORY_H
# define MATRIX_FACTORY_H

# include <math.h>
# include "libft.h"
# include "defines.h"
# include "graceful.h"

t_matrix_4	matrix_new_identity(void);
t_matrix_4	matrix_new_translation(double x, double y, double z);
t_matrix_4	matrix_new_scale(double factor_x, double factor_y, double factor_z);
t_matrix_4	matrix_new_rotation(double angle_x, double angle_y, double angle_z);
t_matrix_4	matrix_new_projection(\
	double fov, \
	double ratio, \
	double near, \
	double far \
);
t_matrix_4	matrix_new_projection_ortho(\
	double fov, \
	double ratio, \
	double near, \
	double far \
);

#endif
