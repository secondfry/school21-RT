#ifndef INIT_SDL_H
# define INIT_SDL_H

# include "sdl_defines.h"
# include "init_rtv.h"

int	sdl_init(t_sdl *sdl);
void	sdl_loop(t_rtv *rtv, t_sdl *sdl);
void	sdl_clear(t_sdl *sdl);

void	sdl_clear_texture(t_sdl *sdl);

void	imgui_init(t_sdl *sdl, t_imgui *imgui);
void	imgui_clear(t_imgui *imgui);

#endif
