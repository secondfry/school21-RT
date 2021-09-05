/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgui_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:30:32 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:31:26 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMGUI_INIT_H
# define IMGUI_INIT_H

# include "sdl_defines.h"

void	imgui_init(t_sdl *sdl, t_imgui *imgui);
void	imgui_clear(t_imgui *imgui);

#endif
