/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_defines.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:50:10 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:50:12 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_DEFINES_H
# define SDL_DEFINES_H

# include <SDL.h>

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"
# include "cimgui_impl.h"

# include "libft.h"
# include "actually_defines.h"

typedef struct s_sdl
{
	SDL_Window		*window;
	SDL_GLContext	gl_context;
	t_byte			buffer[WIDTH * HEIGHT * 4];
}				t_sdl;

typedef struct s_imgui
{
	ImGuiContext	*ctx;
}				t_imgui;

#endif
