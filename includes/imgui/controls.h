/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:56 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:13:43 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"

void	ig_image_defaults(ImTextureID user_texture_id, const ImVec2 size);
bool	ig_drag_vector(const char *label, void *v);

#endif
