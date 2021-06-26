/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:58:36 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/22 19:27:18 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "libft.h"

# define WIDTH 768
# define HEIGHT 768
# define TITLE "RTv1"

# define M_LN2_F 0.693147180559945309417232121458176568f
# define M_PI_F 3.14159265358979323846264338327950288f
# define M_PI_2F 1.57079632679489661923132169163975144f
# define M_PI_4F 0.785398163397448309615660845819875721f
# define M_SQRT2_F 1.41421356237309504880168872420969808f
# define M_SQRT1_2_F 0.707106781186547524400844362104849039f

# define EPSILON 0.001f

# define DOHUYA 100000

typedef float				*t_matrix_4;
typedef float				*t_vector_4;
typedef float				*t_quaterion;
typedef const float	* const t_const_matrix_4;
typedef const float	* const t_const_vector_4;
typedef const float	* const t_const_quaterion;
typedef int					(*t_mlx_hook)();
typedef t_byte				*t_color;

# define TCRED		0
# define TCGREEN	1
# define TCBLUE		2

# define ERR_MEM							35
# define ERR_READ							25
# define ERR_MAP_INVALID_CHARACTERS			1
# define ERR_OPEN							2
# define ERR_MAP_EMPTY						3
# define ERR_MAP_HAS_EMPTY_LINE				4
# define ERR_MAP_HAS_DIFFERENT_WIDTH_LINES	5
# define ERR_MAP_INVALID_WIDTH				6
# define ERR_MAP_INVALID_HEIGHT				7
# define ERR_MAP_BLOCKED_PLAYER				8
# define ERR_MAP_SMOL						9
# define ERR_INVALID_DEFINE					10

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	size_t		size_line_int;
	size_t		size_line_char;
}				t_mlx;

# define MAX_SPHERES 10
# define MAX_PLIGHTS 5
# define MAX_DLIGHTS 5

typedef struct	s_sphere
{
	t_vector_4	position;
	t_color		color;
	float		radius;
	t_byte		traits;
}				t_sphere;

typedef struct	s_plight
{
	t_vector_4	position;
	float		intensity;
	t_byte		traits;
}				t_plight;

typedef struct	s_dlight
{
	t_vector_4	direction;
	float		intensity;
	t_byte		traits;
}				t_dlight;

typedef struct s_rtv
{
	t_mlx		*mlx;
	t_byte		options;
	t_byte		flags;
	t_vector_4	camera_position;
	t_vector_4	camera_rotation;
	t_sphere	spheres[MAX_SPHERES];
	float		ambient;
	t_plight	plights[MAX_PLIGHTS];
	t_dlight	dlights[MAX_DLIGHTS];
}					t_rtv;

enum	e_sizes
{
	SSIZE_T_MAX = ((0ul - 1ul) >> 1ul),
	SSIZE_T_MIN = (SSIZE_T_MAX + 1ul),
};

enum	e_flags
{
	FLAG_REDRAW = (1u << 0u),
	FLAG_INVALIDATE_POSITION = (1u << 1u),
	FLAG_INVALIDATE_ROTATION = (1u << 2u),
};

enum	e_traits
{
	TRAIT_EXISTS = (1u << 0u),
};

enum	e_options
{
	OPTION_ART = (1u << 0u),
};

/*
** === EVENTS ===
** https://tronche.com/gui/x/xlib/events/processing-overview.html
** https://refspecs.linuxfoundation.org/LSB_1.3.0/gLSB/gLSB/libx11-ddefs.html
*/
# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define EVENT_BUTTON_PRESS		4
# define EVENT_BUTTON_RELEASE	5
# define EVENT_MOTION_NOTIFY	6
# define EVENT_EXPOSE			12

/*
** Sent on XDestroyWindow or XDestroySubwindows.
*/
# define EVENT_DESTROY_NOTIFY	17

/*
** Sent on minimize.
*/
# define EVENT_UNMAP_NOTIFY		18

/*
** Sent on unhide.
*/
# define EVENT_MAP_NOTIFY		19

/*
** Sent on changes to a window's state,
** such as size, position, border, and stacking order.
*/
# define EVENT_CONFIGURE_NOTIFY	22

/*
** Sent on client XSendEvent call (X press).
*/
# define EVENT_CLIENT_MESSAGE	33

/*
** === MASKS ===
*/
enum			e_masks
{
	NO_EVENT_MASK = (0L),
	KEY_PRESS_MASK = (1L << 0),
	KEY_RELEASE_MASK = (1L << 1),
	BUTTON_PRESS_MASK = (1L << 2),
	BUTTON_RELEASE_MASK = (1L << 3),
	ENTER_WINDOW_MASK = (1L << 4),
	LEAVE_WINDOW_MASK = (1L << 5),
	POINTER_MOTION_MASK = (1L << 6),
	POINTER_MOTION_HINT_MASK = (1L << 7),
	BUTTON1_MOTION_MASK = (1L << 8),
	BUTTON2_MOTION_MASK = (1L << 9),
	BUTTON3_MOTION_MASK = (1L << 10),
	BUTTON4_MOTION_MASK = (1L << 11),
	BUTTON5_MOTION_MASK = (1L << 12),
	BUTTON_MOTION_MASK = (1L << 13),
	KEYMAP_STATE_MASK = (1L << 14),
	EXPOSURE_MASK = (1L << 15),
	VISIBILITY_CHANGE_MASK = (1L << 16),
	STRUCTURE_NOTIFY_MASK = (1L << 17),
	RESIZE_REDIRECT_MASK = (1L << 18),
	SUBSTRUCTURE_NOTIFY_MASK = (1L << 19),
	SUBSTRUCTURE_REDIRECT_MASK = (1L << 20),
	FOCUS_CHANGE_MASK = (1L << 21),
	PROPERTY_CHANGE_MASK = (1L << 22),
	COLORMAP_CHANGE_MASK = (1L << 23),
	OWNER_GRAB_BUTTON_MASK = (1L << 24),
};

/*
** === KEYCODES ===
*/
# ifdef __APPLE__
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_F		3
#  define KEY_G		5
#  define KEY_Q		12
#  define KEY_W		13
#  define KEY_E		14
#  define KEY_R		15
#  define KEY_T		17
#  define KEY_Z		6
#  define KEY_X		7
#  define KEY_C		8
#  define KEY_ESC	53
# else
#  define KEY_A		97
#  define KEY_C		99
#  define KEY_D		100
#  define KEY_E		101
#  define KEY_F		102
#  define KEY_G		103
#  define KEY_H		104
#  define KEY_Q		113
#  define KEY_R		114
#  define KEY_S		115
#  define KEY_T		116
#  define KEY_W		119
#  define KEY_X		120
#  define KEY_Z		122
#  define KEY_ESC	65307
# endif

# define MOUSE_1			1
# define MOUSE_2			2
# define MOUSE_WHEEL_OUT	5
# define MOUSE_WHEEL_IN		4

#endif
