/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:37:42 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 00:23:57 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/window_controls.h"
#include "rtv.h"
#include "imgui/controls.h"
#include "loop/loop_hook_invalidate.h"
#include "imgui/window_controls_spheres.h"
#include "stb_image_write.h"
#include "imgui/window_controls_filters.h"
#include <time.h>

static void	imgui_planes_group(t_rtv *rtv)
{
	static bool	textured = false;

	if (!ig_group_top_default("Planes"))
		return ;
	igPushID_Str("Planes");
	if (ig_group_default("Plane #0", true))
	{
		igPushID_Str("Plane #0");
		if (igCheckbox("textured", &textured))
		{
			if (textured)
				rtv->planes[0].traits |= TRAIT_TEXTURED;
			else
				rtv->planes[0].traits -= TRAIT_TEXTURED;
			rtv->flags |= FLAG_REDRAW;
		}
		if (ig_drag_vector("scale", &rtv->textures[0].scale.x))
			rtv->flags |= FLAG_REDRAW;
		if (ig_drag_vector("offset", &rtv->textures[0].offset.x))
			rtv->flags |= FLAG_REDRAW;
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
		rtv->flags |= FLAG_REDRAW;
	}
	if (ig_drag_vector("position", &rtv->slice.position.x))
		rtv->flags |= FLAG_REDRAW;
	if (ig_drag_vector("normal", &rtv->slice.normal.x))
		rtv->flags |= FLAG_REDRAW;
	igPopID();
}

static void	imgui_buttons_group(t_rtv *rtv)
{
	const time_t	now = time(NULL);
	const struct tm	*time = localtime(&now);
	static char		buffer[100];

	if (!ig_group_top_default("BUTTONS bruh"))
		return ;
	igPushID_Str("BUTTONS bruh");
	strftime(buffer, sizeof(buffer) - 1, "%Y%m%d%H%M%S.bmp", time);
	if (igButton("Screenshot", (ImVec2){0, 0}))
		stbi_write_bmp(buffer, WIDTH, HEIGHT, 4, rtv->sdl->buffer);
	igPopID();
}

void	imgui_window_controls(t_rtv *rtv)
{
	igBegin("RT controls", 0, ImGuiWindowFlags_NoMove);
	imgui_spheres_group(rtv);
	imgui_planes_group(rtv);
	imgui_camera_group(rtv);
	imgui_cropping_plane_group(rtv);
	imgui_filters_group(rtv);
	imgui_buttons_group(rtv);
	igEnd();
}
