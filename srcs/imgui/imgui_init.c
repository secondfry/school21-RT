/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgui_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:29:21 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:32:48 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/imgui_init.h"
#include "sdl_defines.h"

#if defined(__APPLE__)

// GL 3.2 Core + GLSL 150
static void	imgui_opengl_platform_init(void)
{
	const char	*glsl_version = "#version 150";

	ImGui_ImplOpenGL3_Init(glsl_version);
}

#else

// GL 3.0 + GLSL 130
static void	imgui_opengl_platform_init(void)
{
	const char	*glsl_version = "#version 130";

	ImGui_ImplOpenGL3_Init(glsl_version);
}

#endif

void	imgui_init(t_sdl *sdl, t_imgui *imgui)
{
	igDebugCheckVersionAndDataLayout("1.84.1", \
		sizeof(ImGuiIO), sizeof(ImGuiStyle), sizeof(ImVec2), sizeof(ImVec4), \
		sizeof(ImDrawVert), sizeof(ImDrawIdx) \
	);
	imgui->ctx = igCreateContext(NULL);
	igStyleColorsDark(igGetStyle());
	ImGui_ImplSDL2_InitForOpenGL(sdl->window, sdl->gl_context);
	imgui_opengl_platform_init();
}

void	imgui_clear(t_imgui *imgui)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	igDestroyContext(imgui->ctx);
}
