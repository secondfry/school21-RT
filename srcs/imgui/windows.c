/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:01:55 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 16:10:10 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/windows.h"
#include <SDL_opengl.h>
#include "cimgui.h"
#include "rtv.h"
#include "figures.h"
#include "imgui/controls.h"
#include "loop/loop_hook_invalidate.h"

bool	g_show_demo_window = true;

void	imgui_window_texture(GLuint texture_id)
{
	igBegin("RT", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove \
		| ImGuiWindowFlags_NoCollapse);
	ig_image_defaults((void *)(intptr_t)texture_id, (ImVec2){WIDTH, HEIGHT});
	igEnd();
}

void	imgui_window_debug(void)
{
	if (g_show_demo_window)
		igShowDemoWindow(&g_show_demo_window);
}

void	imgui_spheres_group(t_rtv *rtv)
{
	if (igTreeNodeEx_Str("Spheres", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader))
	{
		igPushID_Str("Spheres");
		if (igTreeNodeEx_Str("Sphere #0", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_NoTreePushOnOpen))
		{
			igPushID_Str("Sphere #0");
			if (ig_drag_vector("vec_c", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
				invalidate_sphere_vectors(rtv, rtv->spheres[0]);
			igPopID();
		}
		igPopID();
	}
}

void	imgui_camera_group(t_rtv *rtv)
{
	if (igTreeNodeEx_Str("Camera", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader))
	{
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
}

void	imgui_cropping_plane_group(t_rtv *rtv)
{
	static bool	checkbox = false;

	if (igTreeNodeEx_Str("Cropping plane (slice)", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader))
	{
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
}

void	imgui_window_controls(t_rtv *rtv)
{
	igBegin("RT controls", 0, ImGuiWindowFlags_NoMove);
	imgui_spheres_group(rtv);
	imgui_camera_group(rtv);
	imgui_cropping_plane_group(rtv);
	igEnd();
}
