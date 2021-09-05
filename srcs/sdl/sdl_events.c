/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:09:03 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:09:46 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl/sdl_events.h"
#include "libft.h"
#include "sdl_defines.h"

t_byte	sdl_handle_event(t_sdl *sdl)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_WINDOWEVENT \
			&& event.window.event == SDL_WINDOWEVENT_CLOSE \
			&& event.window.windowID == SDL_GetWindowID(sdl->window) \
		)
			return (1);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			return (1);
	}
	return (0);
}
