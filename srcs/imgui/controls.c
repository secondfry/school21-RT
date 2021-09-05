/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:23 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:13:50 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/controls.h"

void	ig_image_defaults(ImTextureID user_texture_id, const ImVec2 size)
{
	igImage(
		user_texture_id,
		size,
		(ImVec2){0, 0},
		(ImVec2){1, 1},
		(ImVec4){1, 1, 1, 1},
		(ImVec4){0, 0, 0, 0} \
	);
}

bool	ig_drag_vector(const char *label, void *v)
{
	return (igDragScalarN(
			label,
			ImGuiDataType_Double,
			v,
			3,
			0.05f,
			0,
			0,
			"%.3f",
			0
		)
	);
}
