/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:38:37 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 20:21:49 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "raytrace/raytrace_texture.h"

static t_light_params	get_light_params(t_rtv *rtv, t_intersection *intr)
{
	if (intr->type == ISPHERE)
		return ((t_light_params){\
			.vec_c = rtv->spheres[intr->idx].vectors[VCTR_SPHERE_C], \
			.color = rtv->spheres[intr->idx].color, \
			.specular = rtv->spheres[intr->idx].specular, \
			.reflection = rtv->spheres[intr->idx].reflection, \
			.refraction = rtv->spheres[intr->idx].refraction \
		});
	if (intr->type == IPLANE)
		return ((t_light_params){\
			.vec_c = rtv->planes[intr->idx].position, \
			.color = rtv->planes[intr->idx].color, \
			.specular = rtv->planes[intr->idx].specular, \
			.reflection = rtv->planes[intr->idx].reflection \
		});
	if (intr->type == ICYLINDER)
		return ((t_light_params){\
			.vec_c = rtv->cylinders[intr->idx].vectors[VCTR_CYLINDER_C0], \
			.color = rtv->cylinders[intr->idx].color, \
			.specular = rtv->cylinders[intr->idx].specular, \
			.reflection = rtv->cylinders[intr->idx].reflection \
		});
	if (intr->type == ICONE)
		return ((t_light_params){\
			.vec_c = rtv->cones[intr->idx].vectors[VCTR_CONE_C0], \
			.color = rtv->cones[intr->idx].color, \
			.specular = rtv->cones[intr->idx].specular, \
			.reflection = rtv->cones[intr->idx].reflection \
		});
	return ((t_light_params){});
}



static t_color	pre_light(t_rtv *rtv, t_worker_data *data, t_intersection *intr)
{
	const t_light_params	params = get_light_params(rtv, intr);
	double					intensity;
	t_color                 color;
	t_color                 reflection_color;
	t_color                 refraction_color;

	vector_set_by_value(&params.vec_p, vector_add(\
		data->vectors[VCTR_O], \
		vector_mult(data->vectors[VCTR_D], intr->distance) \
	));
	vector_set_by_value(\
		&params.vec_n, find_normal(rtv, intr, &params));
	vector_set_by_value(&params.vec_v, vector_mult(data->vectors[VCTR_D], -1));
	intensity = light(rtv, &params);
	check_texture(rtv, &params, intr);
	color = *color_mult((void *)&params.color, intensity);
	if (data->depth <= 0)
		return (color);
	if (params.reflection > 0)
	{
		reflection_color = find_reflection(rtv, params, *data);
		color = *color_add(color_mult(&color, 1.0 - params.reflection), \
						   color_mult(&reflection_color,params.reflection));
	}
	if (params.refraction > 0)
	{
		refraction_color = find_refraction(rtv, params, *data);
		color = *color_add(&color, color_mult(&refraction_color,params.refraction));
	}
	return (color);
}

t_vector_4 find_reflect_ray(t_vector_4 ray, t_vector_4 normal)
{
    return (vector_sub(vector_mult(normal, 2*vector_dot(normal, ray)), ray));
}

t_vector_4 find_refract_ray(t_vector_4 ray, t_vector_4 normal, double refr_coef)
{
	double cosi = -1 * vector_dot(ray, normal)/vector_length(ray);
    double eta;
	// double k;

	// eta = 1 / refr_coef;
    // if (cosi < 0) 
	// {
    //     cosi = -cosi;
	// 	eta = 1 / eta;
	// 	vector_set_by_value(&normal, vector_mult(normal, -1));
    // }
    // k = 1 - eta*eta*(1 - cosi*cosi);
	// if (k < 0)
	// 	return ((t_vector_4){0, 0, 0 ,0});

	eta = 2.0 - refr_coef;
    cosi = vector_dot(normal, ray);
    return vector_sub(vector_mult(ray, eta), vector_mult(normal, (-cosi + eta * cosi)));
    // return vector_add(vector_mult(ray, eta), vector_mult(normal, eta * cosi - sqrt(k)));
}


t_color  find_reflection(t_rtv *rtv, t_light_params params, t_worker_data data)
{
	t_vector_4 reflect_ray;

	vector_set_by_value(&reflect_ray, find_reflect_ray(params.vec_v, params.vec_n));
	vector_set(data.vectors + VCTR_O, &params.vec_p);
	vector_set(data.vectors + VCTR_D, &reflect_ray);
	data.doubles[D_DOT_D] = vector_dot(\
		data.vectors[VCTR_D], \
		data.vectors[VCTR_D] \
	);
	data.depth -= 1;	
	return (raytrace(rtv, &data, 0.1f, 1.0 / 0.0));
}

t_color  find_refraction(t_rtv *rtv, t_light_params params, t_worker_data data)
{
	t_vector_4 refract_ray;

	vector_set_by_value(&refract_ray, find_refract_ray(params.vec_v, params.vec_n, \
													params.refraction));
	vector_set(data.vectors + VCTR_O, &params.vec_p);
	vector_set(data.vectors + VCTR_D, &refract_ray);
	data.doubles[D_DOT_D] = vector_dot(\
		data.vectors[VCTR_D], \
		data.vectors[VCTR_D] \
	);
	data.depth -= 1;	
	return (raytrace(rtv, &data, 0.1f, 1.0 / 0.0));
}

t_color	raytrace(
	t_rtv *rtv,
	t_worker_data *data,
	double t_min,
	double t_max
)
{
	t_intersection	intr;

	intr = intersection_closest(\
		rtv, \
		&((t_intersect_params){\
			data->vectors[VCTR_O], \
			data->vectors[VCTR_D], \
			t_min, \
			t_max \
		}) \
	);
	if (intr.distance == 1.0 / 0.0)
		return ((t_color){0, 0, 0});
	return (pre_light(rtv, data, &intr));
}

t_color	process_pixel(t_rtv *rtv, short xc, short yc)
{
	const t_vector_4	vec_d = vector_normalize(matrix_on_vector(
		rtv->camera_rotation,
		(t_vector_4){(double) xc / WIDTH, (double) yc / HEIGHT, 1.f, 0}
	));
	t_worker_data		data;

	vector_set(data.vectors + VCTR_O, &rtv->camera_position);
	vector_set(data.vectors + VCTR_D, &vec_d);
	data.doubles[D_DOT_D] = vector_dot(\
		data.vectors[VCTR_D], \
		data.vectors[VCTR_D] \
	);
	data.depth = DEPTH;
	return (raytrace(rtv, &data, 0.1f, 1.0 / 0.0));
}
