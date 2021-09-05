/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:03:46 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:08:15 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWS_H
# define WINDOWS_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

# include <SDL_opengl.h>
# include "rtv.h"

void	imgui_window_texture(GLuint texture_id);
void	imgui_window_debug(void);
void	imgui_window_controls(t_rtv *rtv);

#endif
