/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:49:10 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:49:13 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_SPHERE_H
# define INTERSECTION_SPHERE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"
# include "intersection_common.h"

typedef struct s_intersection_sphere
{
	t_vector_4	vec_c;
	t_vector_4	vec_co;
	double		a;
	double		b;
	double		c;
	double		cubed;
	double		sqrt;
}				t_intersection_sphere;

t_intersection	intersection_sphere_closest(\
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
