/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:23 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 21:15:38 by oadhesiv         ###   ########.fr       */
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

bool	ig_drag_vector(const char *label, const double *v)
{
	return (igDragScalarN(
			label,
			ImGuiDataType_Double,
			(void *)v,
			3,
			0.05f,
			0,
			0,
			"%.3f",
			0
		)
	);
}

bool	ig_drag_double(const char *label, const double *v)
{
	static double	min = 0.0;
	static double	max = 1.0 / 0.0;

	return (igDragScalar(
			label,
			ImGuiDataType_Double,
			(void *)v,
			0.05f,
			&min,
			&max,
			"%.3f",
			0
		)
	);
}

bool	ig_group_top_default(const char *label)
{
	return (igTreeNodeEx_Str(\
		label, \
		ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader \
	));
}

bool	ig_group_default(const char *label, bool first)
{
	if (first)
		return (igTreeNodeEx_Str(\
			label, \
			ImGuiTreeNodeFlags_DefaultOpen \
				| ImGuiTreeNodeFlags_NoTreePushOnOpen \
		));
	return (igTreeNodeEx_Str(\
		label, \
		ImGuiTreeNodeFlags_NoTreePushOnOpen \
	));
}
