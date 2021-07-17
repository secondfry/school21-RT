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
			0 \
		}), sizeof(t_cone));
		i++;
	}
}

static void	init_rtv_unnormed(t_rtv *rtv)
{
	const float angle10 = 10.f * M_PI_F / 180.f;
	const float cos = cosf(angle10);
	const float cos2 = cos * cos;
	const t_vector_4 cone_C0 = vector_new(-1.f, 0.f, 10.f, 1.f);
	const t_vector_4 cone_C1 = vector_new(-2.f, 10.f, 10.f, 1.f);

	ft_memcpy(rtv->cones + 0, &((t_cone) {
		{
			cone_C0,
			cone_C1,
			vector_sub(cone_C1, cone_C0)
		},
		color_new(255, 0, 255),
		angle10,
		cos2,
		1000.0f,
		TRAIT_EXISTS
	}), sizeof(t_cone));

	const t_vector_4 cylinder_C0 = vector_new(1.f, 0.f, 10.f, 1.f);
	const t_vector_4 cylinder_C1 = vector_new(2.f, 10.f, 10.f, 1.f);

	ft_memcpy(rtv->cylinders + 0, &((t_cylinder) {
		{
			cylinder_C0,
			cylinder_C1,
			vector_sub(cylinder_C1, cylinder_C0)
		},
		color_new(255, 255, 255),
		1.f,
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
		500.0f,
		TRAIT_EXISTS
	}), sizeof(t_cylinder));
}

void	init_rtv_objects(t_rtv *rtv)
{
	init_rtv_spheres(rtv);
	init_rtv_planes(rtv);
	init_rtv_cylinders(rtv);
	init_rtv_cones(rtv);
	init_rtv_unnormed(rtv);
}
