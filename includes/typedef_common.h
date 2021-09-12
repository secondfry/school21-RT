/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef_common.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:50:15 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:50:17 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_COMMON_H
# define TYPEDEF_COMMON_H

# include "libft.h"

typedef const struct s_vector_4
{
	double	x;
	double	y;
	double	z;
	double	w;
}						t_vector_4;

typedef struct s_color
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
}				t_color;

typedef double			*t_matrix_4;
typedef double			*t_quaternion;
typedef const double	*t_const_matrix_4;
typedef const double	*t_const_quaternion;

typedef struct s_texture
{
	t_byte		*data;
	int			width;
	int			height;
	t_vector_4	offset;
	t_vector_4	scale;
}				t_texture;

#endif
