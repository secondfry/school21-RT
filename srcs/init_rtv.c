#include "init_rtv.h"

// NOTE(secondfry): после завершения валидатора
// эти функции уместяться в 25 строк.

static void	init_rtv_spheres(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_SPHERES)
	{
		ft_memcpy(rtv->spheres + i, &((t_sphere){
			{{0, 0, 0, 0}}, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_sphere));
		i++;
	}
	ft_memcpy(rtv->spheres + 0, &((t_sphere){
		{{0, -1.f, 3, 1}}, \
		color_new(255, 0, 0), \
		1.0f, \
		500.f, \
		TRAIT_EXISTS \
	}), sizeof(t_sphere));
	ft_memcpy(rtv->spheres + 1, &((t_sphere){
		{{-2, 0, 4, 1}}, \
		color_new(0, 255, 0), \
		1.0f, \
		10.f, \
		TRAIT_EXISTS \
	}), sizeof(t_sphere));
	ft_memcpy(rtv->spheres + 2, &((t_sphere){
		{{2, 0, 4, 1}}, \
		color_new(0, 0, 255), \
		1.0f, \
		500.f, \
		TRAIT_EXISTS \
	}), sizeof(t_sphere));
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
	// ft_memcpy(rtv->planes + 0, &((t_plane){
	// 	vector_new(0, -1.f, 0, 1),
	// 	vector_new(0, 1.f, 0, 0),
	// 	color_new(255, 255, 0),
	// 	1000.0f,
	// 	TRAIT_EXISTS
	//}), sizeof(t_plane));
}

static void	init_rtv_cylinders(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_CYLINDERS)
	{
		ft_memcpy(rtv->cylinders + i, &((t_cylinder){
			{{0, 0, 0, 0}, {0, 0, 0, 0}}, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_cylinder));
		i++;
	}
	ft_memcpy(rtv->cylinders + 0, &((t_cylinder){
		{vector_new(1.f, 0.f, 10.f, 1.f), vector_new(2.f, 10.f, 10.f, 1.f)}, \
		color_new(255, 255, 255), \
		1.f, \
		1000.0f, \
		TRAIT_EXISTS \
	}), sizeof(t_cylinder));
}

static void	init_rtv_cones(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_CONES)
	{
		ft_memcpy(rtv->cones + i, &((t_cone){
			{{0, 0, 0, 0}, {0, 0, 0, 0}}, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_cone));
		i++;
	}
	ft_memcpy(rtv->cones + 0, &((t_cone){
		{vector_new(-1.f, 0.f, 10.f, 1.f), vector_new(-2.f, 10.f, 10.f, 1.f)}, \
		color_new(255, 0, 255), \
		10.f * M_PI_F / 180.f, \
		1000.0f, \
		TRAIT_EXISTS \
	}), sizeof(t_cone));
}

static void	init_rtv_objects(t_rtv *rtv)
{
	init_rtv_spheres(rtv);
	init_rtv_planes(rtv);
	init_rtv_cylinders(rtv);
	init_rtv_cones(rtv);
}

static void	init_rtv_plights(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_PLIGHTS)
	{
		ft_memcpy(rtv->plights + i, &((t_plight){
			{0, 0, 0, 0}, \
			0, \
			0 \
		}), sizeof(t_plight));
		i++;
	}
}

static void	init_rtv_dlights(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_DLIGHTS)
	{
		ft_memcpy(rtv->dlights + i, &((t_dlight){
			{0, 0, 0, 0}, \
			0, \
			0 \
		}), sizeof(t_dlight));
		i++;
	}
}

static void	init_rtv_ambient(t_rtv *rtv)
{
	rtv->ambient = 0.0f;
}

static void	init_rtv_lights(t_rtv *rtv)
{
	init_rtv_plights(rtv);
	init_rtv_dlights(rtv);
	init_rtv_ambient(rtv);
}

static void	init_rtv_scene(t_rtv *rtv)
{
	init_rtv_objects(rtv);
	init_rtv_lights(rtv);
}

static void	init_rtv_common(t_rtv *rtv)
{
	rtv->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	ft_memcpy(
		(void *)&rtv->camera_position, \
		&((t_vector_4){0.f, 0.f, -10.f, 1.f}), \
		sizeof(t_vector_4) \
	);
	rtv->camera_angles[AROLL] = 0;
	rtv->camera_angles[AYAW] = 0;
	rtv->camera_angles[APITCH] = 0;
	rtv->camera_rotation = matrix_new_identity();
}

void	init_rtv(t_rtv *rtv)
{
	init_rtv_common(rtv);
	init_rtv_scene(rtv);
}
