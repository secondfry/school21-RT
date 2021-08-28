#ifndef SDL_H
# define SDL_H

# include "defines.h"

# include <SDL.h>

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"
# include "cimgui_impl.h"

typedef struct s_sdl
{
	SDL_Window		*window;
	SDL_GLContext	gl_context;
	t_byte			buffer[WIDTH * HEIGHT * 4];
} t_sdl;

typedef struct s_imgui
{
	ImGuiContext	*ctx;
} t_imgui;

#endif
