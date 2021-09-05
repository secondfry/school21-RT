/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:11:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:06:40 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop/loop_sdl.h"
#include "cimgui.h"
#include "cimgui_impl.h"
#include <SDL_opengl.h>
#include "imgui/windows.h"

static GLuint	create_texture(t_rtv *rtv)
{
	GLuint	texture_id;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		WIDTH,
		HEIGHT,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		rtv->sdl->buffer \
	);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (texture_id);
}

static void	imgui_new_frame(void)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	igNewFrame();
}

static void	imgui_render(t_rtv *rtv)
{
	const ImGuiIO	*io = igGetIO();

	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(rtv->sdl->window);
}

static void	delete_texture(GLuint texture_id)
{
	glDeleteTextures(1, &texture_id);
}

void	loop_sdl(t_rtv *rtv)
{
	const GLuint	texture_id = create_texture(rtv);

	imgui_new_frame();
	imgui_window_texture(texture_id);
	imgui_window_debug();
	imgui_window_controls(rtv);
	imgui_render(rtv);
	delete_texture(texture_id);
}
