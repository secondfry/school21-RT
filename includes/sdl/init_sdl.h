/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:10:44 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:10:45 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SDL_H
# define INIT_SDL_H

# include "sdl_defines.h"
# include "rtv.h"

int		sdl_init(t_sdl *sdl);
void	sdl_loop(t_rtv *rtv, t_sdl *sdl);
void	sdl_clear(t_sdl *sdl);

void	sdl_clear_texture(t_sdl *sdl);

void	imgui_init(t_sdl *sdl, t_imgui *imgui);
void	imgui_clear(t_imgui *imgui);

#endif
