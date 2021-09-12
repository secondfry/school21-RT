/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:49:43 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:49:44 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include <math.h>
# include "libft.h"
# include "defines.h"
# include "graceful.h"

t_quaternion	quaternion_new(double angle_x, double angle_y, double angle_z);
t_matrix_4		quaternion_to_matrix(t_const_quaternion self);

#endif
