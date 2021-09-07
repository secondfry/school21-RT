#ifndef RTV_H
# define RTV_H

# ifndef RT_SERVER
#  include "sdl_defines.h"
#  include <SDL.h>
# endif

# include "typedef_common.h"
# include "figures.h"
# include "lights.h"

# define MAX_SPHERES	5
# define MAX_PLANES		10
# define MAX_CYLINDERS	10
# define MAX_CONES		10

# define MAX_PLIGHTS	5
# define MAX_DLIGHTS	5
# define MAX_TEXTURES	1

# ifdef RT_SERVER

typedef void		*t_sdl;
typedef void		*t_sdl_window;

# else

typedef SDL_Window	t_sdl_window;

# endif

typedef struct s_rtv
{
	t_sdl			*sdl;
	t_byte			options;
	t_byte			flags;
	t_vector_4		camera_position;
	t_vector_4		camera_angles;
	t_matrix_4		camera_rotation;
	t_sphere		spheres[MAX_SPHERES];
	t_plane			planes[MAX_PLANES];
	t_plane			slice;
	t_cylinder		cylinders[MAX_CYLINDERS];
	t_cone			cones[MAX_CONES];
	double			ambient;
	t_plight		plights[MAX_PLIGHTS];
	t_dlight		dlights[MAX_DLIGHTS];
	char			*filename;
	t_sdl_window	*window;
	t_texture		textures[MAX_TEXTURES];
}					t_rtv;

#endif
