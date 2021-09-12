/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:46:23 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:47:01 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "typedef_common.h"

# define FIGURES 4

# define MAX_VECTORS_SPHERE 2

# define VCTR_SPHERE_C 0
# define VCTR_SPHERE_CO 1

typedef struct s_sphere
{
	t_vector_4	vectors[MAX_VECTORS_SPHERE];
	t_color		color;
	double		radius_squared;
	double		specular;
	double		reflection;
	t_byte		texture_id;
	t_byte		traits;
}				t_sphere;

typedef struct s_plane
{
	t_vector_4	position;
	t_vector_4	normal;
	t_color		color;
	double		specular;
	double		reflection;
	t_byte		traits;
}				t_plane;

# define MAX_VECTORS_CYLINDER 3

# define VCTR_CYLINDER_C0 0
# define VCTR_CYLINDER_C1 1
# define VCTR_CYLINDER_C0C1 2

typedef struct s_cylinder
{
	t_vector_4	vectors[MAX_VECTORS_CYLINDER];
	t_color		color;
	double		radius2;
	double		specular;
	double		reflection;
	t_byte		traits;
}				t_cylinder;

# define MAX_VECTORS_CONE 3

# define VCTR_CONE_C0	0
# define VCTR_CONE_C1	1
# define VCTR_CONE_C0C1	2

typedef struct s_cone
{
	t_vector_4	vectors[MAX_VECTORS_CONE];
	t_color		color;
	double		angle;
	double		cos;
	double		cos2;
	double		specular;
	double		reflection;
	t_byte		traits;
}				t_cone;

#endif
