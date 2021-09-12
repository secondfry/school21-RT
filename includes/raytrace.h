/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:49:55 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:50:38 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "typedef_common.h"
# include "rtv.h"
# include "vector.h"
# include "color.h"
# include "intersection.h"
# include "matrix_utils.h"
# include "normal.h"
# include "raytrace_light.h"

// FIXME(secondfry): unused
typedef struct s_pre_light
{
	t_light_params	params;
	t_vector_4		vec_p;
	t_vector_4		vec_n;
	t_vector_4		vec_v;
	double			intensity;
}				t_pre_light;

t_color	process_pixel(t_rtv *rtv, short xc, short yc);
t_color	raytrace(t_rtv *rtv, t_worker_data *data, double t_min, double t_max);
t_color	find_reflection(t_rtv *rtv, t_light_params params, t_worker_data data);

#endif
