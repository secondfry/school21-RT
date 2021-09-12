/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:56 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 14:23:00 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# include "cimgui.h"

void	ig_image_defaults(ImTextureID user_texture_id, const ImVec2 size);
bool	ig_drag_vector(const char *label, const double *v);
bool	ig_drag_double(const char *label, const double *v, const double max);
bool	ig_group_top_default(const char *label);
bool	ig_group_default(const char *label, bool first);

#endif
