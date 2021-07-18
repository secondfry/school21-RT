#include "init_rtv.h"

static void	init_rtv_spheres(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_SPHERES)
	{
		ft_memcpy(rtv->spheres + i, &((t_sphere){
			{{0, 0, 0, 0}, {0, 0, 0, 0}}, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_sphere));
		i++;
	}
}

static void	init_rtv_planes(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_PLANES)
	{
		ft_memcpy(rtv->planes + i, &((t_plane){
			{0, 0, 0, 0}, \
			{0, 0, 0, 0}, \
			0, \
			0, \
			0 \
		}), sizeof(t_plane));
		i++;
	}
}

static void	init_rtv_cylinders(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_CYLINDERS)
	{
		ft_memcpy(rtv->cylinders + i, &((t_cylinder){
			{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_cylinder));
		i++;
	}
}

static void	init_rtv_cones(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_CONES)
	{
		ft_memcpy(rtv->cones + i, &((t_cone){
			{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, \
			0, \
			0, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_cone));
		i++;
	}
}

#include <stdio.h>
static void	init_rtv_unnormed(t_rtv *rtv)
{
	const float angle10 = 10.f * M_PI_F / 180.f;
	const float cos = cosf(angle10);
	const float cos2 = cos * cos;
	const t_vector_4 cone_C0 = vector_new(-1.f, 0.f, 10.f, 1.f);
	const t_vector_4 cone_C1 = vector_new(-2.f, 10.f, 10.f, 1.f);

	// ft_memcpy(rtv->cones + 0, &((t_cone) {
	// 	{
	// 		cone_C0,
	// 		cone_C1,
	// 		vector_normalize(vector_sub(cone_C1, cone_C0))
	// 	},
	// 	color_new(255, 0, 255),
	// 	angle10,
	// 	cos,
	// 	cos2,
	// 	1000.0f,
	// 	TRAIT_EXISTS
	// }), sizeof(t_cone));

	const t_vector_4 cylinder_C0 = vector_new(1.f, 0.f, 10.f, 1.f);
	const t_vector_4 cylinder_C1 = vector_new(2.f, 10.f, 10.f, 1.f);

	ft_memcpy(rtv->cylinders + 0, &((t_cylinder) {
		{
			cylinder_C0,
			cylinder_C1,
			vector_normalize(vector_sub(cylinder_C1, cylinder_C0))
		},
		color_new(255, 255, 255),
		1.f,
		1000.0f,
		TRAIT_EXISTS
	}), sizeof(t_cylinder));

	// t_vector_4 vec_norm = vector_normalize(vector_sub(cone_C1, cone_C0));
	// printf("\n\n\n\nREAL_VEC_NORM = {%f, %f, %f, %f}\n\n\n\n", vec_norm.x, vec_norm.y, vec_norm.z, vec_norm.w);
	ft_memcpy(rtv->cylinders + 1, &((t_cylinder) {
		{
			cone_C0,
			cone_C1,
			vector_normalize(vector_sub(cone_C1, cone_C0))
		},
		color_new(255, 0, 255),
		0.1f,
		1000.0f,
		TRAIT_EXISTS
	}), sizeof(t_cylinder));

	const t_vector_4 sphere_C = vector_new(0.f, -1.f, 3.f, 1.f);

	ft_memcpy(rtv->spheres + 0, &((t_sphere) {
		{
			sphere_C
		},
		color_new(255, 0, 0),
		1.f,
		100.0f,
		TRAIT_EXISTS
	}), sizeof(t_sphere));

	ft_memcpy(rtv->spheres + 1, &((t_sphere) {
		{
			vector_new(-2.f, 0.f, 4.f, 1.f)
		},
		color_new(0, 255, 0),
		1.f,
		10.0f,
		TRAIT_EXISTS
	}), sizeof(t_sphere));

	ft_memcpy(rtv->spheres + 2, &((t_sphere) {
		{
			vector_new(2.f, 0.f, 4.f, 1.f)
		},
		color_new(0, 0, 255),
		1.f,
		1000.0f,
		TRAIT_EXISTS
	}), sizeof(t_sphere));

	ft_memcpy(rtv->planes + 0, &((t_plane) {
		vector_new(2.f, -10.f, 4.f, 1.f),
		vector_normalize(vector_new(0.f, 1.f, 0.f, 0.f)),
		color_new(255, 255, 0),
		1.0f,
		TRAIT_EXISTS
	}), sizeof(t_plane));

	// ft_memcpy(rtv->planes + 1, &((t_plane) {
	// 	vector_new(2.f, 10.f, 4.f, 1.f),
	// 	vector_normalize(vector_new(0.f, -1.f, 0.f, 0.f)),
	// 	color_new(0, 255, 255),
	// 	1.0f,
	// 	TRAIT_EXISTS
	// }), sizeof(t_plane));

	ft_memcpy(rtv->planes + 2, &((t_plane) {
		vector_new(2.f, 10.f, 20.f, 1.f),
		vector_normalize(vector_new(0.f, 0.f, -1.f, 0.f)),
		color_new(0, 127, 255),
		1.0f,
		TRAIT_EXISTS
	}), sizeof(t_plane));
}

void	init_rtv_objects(t_rtv *rtv)
{
	init_rtv_spheres(rtv);
	init_rtv_planes(rtv);
	init_rtv_cylinders(rtv);
	init_rtv_cones(rtv);
	// init_rtv_unnormed(rtv);
}
