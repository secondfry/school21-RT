/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:48:53 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:48:55 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_CONE_H
# define INTERSECTION_CONE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"
# include "intersection_common.h"

typedef struct s_intersection_cone
{
	t_vector_4	vec_c;
	t_vector_4	vec_co;
	t_vector_4	vec_cq;
	double		d_dot_cq;
	double		co_dot_cq;
	double		d_dot_co;
	double		co_dot_co;
	double		cos2;
	double		a;
	double		b;
	double		c;
	double		cubed;
	double		sqrt;
}				t_intersection_cone;

t_intersection	intersection_cone_closest(\
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
