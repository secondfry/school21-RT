#ifndef SDL_H
# define SDL_H

# include <SDL.h>

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"
# include "cimgui_impl.h"

typedef struct s_sdl
{
	SDL_Window		*window;
	SDL_GLContext	gl_context;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_byte			*buffer;
	int				pitch;
} t_sdl;

typedef struct s_imgui
{
	ImGuiContext	*ctx;
} t_imgui;

#endif
