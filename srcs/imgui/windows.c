/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:01:55 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:33:38 by oadhesiv         ###   ########.fr       */
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

void	imgui_window_controls(t_rtv *rtv)
{
	igBegin("RT controls", 0, ImGuiWindowFlags_NoMove);
	igText("First sphere location");
	if (ig_drag_vector("center", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
		invalidate_sphere_vectors(rtv, rtv->spheres[0]);
	igEnd();
}
