/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:10:49 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:30:09 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static t_vector_4	find_reflect_ray(t_vector_4 ray, t_vector_4 normal)
{
	return (vector_sub(vector_mult(normal, 2 * vector_dot(normal, ray)), ray));
}

t_color	find_reflection(t_rtv *rtv, t_light_params params, t_worker_data data)
{
	t_vector_4	reflect_ray;

	vector_set_by_value(&reflect_ray, find_reflect_ray(params.vec_v, \
														params.vec_n));
	vector_set(data.vectors + VCTR_O, &params.vec_p);
	vector_set(data.vectors + VCTR_D, &reflect_ray);
	data.doubles[D_DOT_D] = vector_dot(\
		data.vectors[VCTR_D], \
		data.vectors[VCTR_D] \
	);
	data.depth -= 1;
	return (raytrace(rtv, &data, 0.1f, 1.0 / 0.0));
}
