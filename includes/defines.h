/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:58:36 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 13:46:03 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "actually_defines.h"

# ifdef __cplusplus
#  include "figures.hpp"
#  include "lights.hpp"
#  include "rtv.hpp"
# else
#  include "figures.h"
#  include "lights.h"
#  include "rtv.h"
# endif

# include "libft.h"

typedef struct s_intersection
{
	double	distance;
	t_byte	idx;
	t_byte	type;
}				t_intersection;

# define ISPHERE	0
# define IPLANE		1
# define ICYLINDER	2
# define ICONE		3

# define MAX_VECTORS_WORKER	7
# define MAX_DOUBLES_WORKER	3

# define VCTR_O	0
# define VCTR_D	1

// FIXME(secondfry): unused
# define VCTR_P	2
# define VCTR_N	3
# define VCTR_V	4
# define VCTR_L	5
# define VCTR_R	6

# define D_DOT_D 0

# define DEPTH 3

typedef struct s_worker_data
{
	t_vector_4	vectors[MAX_VECTORS_WORKER];
	double		doubles[MAX_DOUBLES_WORKER];
	int			depth;
}				t_worker_data;

typedef struct s_intersect_params
{
	t_vector_4	vec_o;
	t_vector_4	vec_d;
	double		t_min;
	double		t_max;
}				t_intersect_params;

typedef struct s_light_params
{
	t_vector_4		vec_c;
	t_color			color;
	double			specular;
	double			reflection;
	t_vector_4		vec_p;
	t_vector_4		vec_n;
	t_vector_4		vec_v;
	t_vector_4		vec_l;
	t_intersection	intr;
}				t_light_params;

#endif
