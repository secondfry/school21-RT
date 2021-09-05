/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 13:56:04 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:28:12 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "sdl/init_sdl.h"
#include "loop_hook.h"
#include "sdl/sdl_events.h"
#include "sdl/sdl_gl_attributes.h"

int	sdl_init(t_sdl *sdl)
{
	const int		status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_DisplayMode	dm;

	if (status != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, \
			"Couldn't initialize SDL: %s", SDL_GetError());
		return (status);
	}
	set_attributes();
	SDL_GetCurrentDisplayMode(0, &dm);
	sdl->window = SDL_CreateWindow("RT", \
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, \
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	ft_ptr_check(sdl->window, SDL_GetError(), 0);
	sdl->gl_context = SDL_GL_CreateContext(sdl->window);
	ft_ptr_check(sdl->gl_context, SDL_GetError(), 0);
	SDL_GL_MakeCurrent(sdl->window, sdl->gl_context);
	SDL_GL_SetSwapInterval(1);
	return (0);
}

void	sdl_loop(t_rtv *rtv, t_sdl *sdl)
{
	while (1)
	{
		if (sdl_handle_event(sdl))
			break ;
		loop_hook(rtv);
	}
}

void	sdl_clear(t_sdl *sdl)
{
	SDL_GL_DeleteContext(sdl->gl_context);
	if (sdl->window != NULL)
	{
		SDL_DestroyWindow(sdl->window);
		sdl->window = NULL;
	}
	SDL_Quit();
}
