/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:37:42 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 16:40:33 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/window_controls.h"
#include "rtv.h"
#include "imgui/controls.h"
#include "loop/loop_hook_invalidate.h"

static void	imgui_spheres_group(t_rtv *rtv)
{
	if (!ig_group_top_default("Spheres"))
		return ;
	igPushID_Str("Spheres");
	if (ig_group_default("Sphere #0"))
	{
		igPushID_Str("Sphere #0");
		if (ig_drag_vector("vec_c", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
			invalidate_sphere_vectors(rtv, rtv->spheres[0]);
		igPopID();
	}
	igPopID();
}

static void	imgui_camera_group(t_rtv *rtv)
{
	if (!ig_group_top_default("Camera"))
		return ;
	igPushID_Str("Camera");
	if (ig_drag_vector("position", &rtv->camera_position.x))
	{
		rtv->flags |= FLAG_INVALIDATE_POSITION;
		loop_invalidate_position(rtv);
	}
	if (ig_drag_vector("rotation", &rtv->camera_angles.x))
	{
		rtv->flags |= FLAG_INVALIDATE_ROTATION;
		loop_invalidate_rotation(rtv);
	}
	igPopID();
}

static void	imgui_cropping_plane_group(t_rtv *rtv)
{
	static bool	checkbox = false;

	if (!ig_group_top_default("Cropping plane (slice)"))
		return ;
	igPushID_Str("Cropping plane (slice)");
	if (igCheckbox("enabled", &checkbox))
	{
		if (checkbox)
			rtv->slice.traits |= TRAIT_EXISTS;
		else
			rtv->slice.traits -= TRAIT_EXISTS;
	}
	if (ig_drag_vector("position", &rtv->slice.position.x))
		rtv->flags |= FLAG_REDRAW;
	if (ig_drag_vector("normal", &rtv->slice.normal.x))
		rtv->flags |= FLAG_REDRAW;
	igPopID();
}

void	imgui_window_controls(t_rtv *rtv)
{
	igBegin("RT controls", 0, ImGuiWindowFlags_NoMove);
	imgui_spheres_group(rtv);
	imgui_camera_group(rtv);
	imgui_cropping_plane_group(rtv);
	igEnd();
}
