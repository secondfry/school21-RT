#ifndef RTV_HPP
# define RTV_HPP

# include "typedef_common.h"
# include "figures.hpp"
# include "lights.hpp"

# define MAX_SPHERES	10
# define MAX_PLANES		10
# define MAX_CYLINDERS	10
# define MAX_CONES		10

# define MAX_PLIGHTS	5
# define MAX_DLIGHTS	5

typedef struct s_rtv
{
	t_mlx		*mlx;
	t_byte		options;
	t_byte		flags;
	t_vector_4	camera_position;
	float		camera_angles[3];
	t_matrix_4	camera_rotation;
	t_sphere	spheres[MAX_SPHERES];
	t_plane		planes[MAX_PLANES];
	t_cylinder	cylinders[MAX_CYLINDERS];
	t_cone		cones[MAX_CONES];
	float		ambient;
	t_plight	plights[MAX_PLIGHTS];
	t_dlight	dlights[MAX_DLIGHTS];

	s_rtv() : camera_position{ 0.f, 0.f, 0.f, 1.f } {}
} t_rtv;

#endif