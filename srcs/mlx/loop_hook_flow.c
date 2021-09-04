/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secondfry <secondfry@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:49:39 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/04 20:18:43 by secondfry        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

bool	g_show_demo_window = true;

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

static void	imgui_window_texture(GLuint texture_id)
{
	igBegin("RT", 0, 0);
	ig_image_defaults((void *)(intptr_t)texture_id, (ImVec2){WIDTH, HEIGHT});
	igEnd();
}

static void	imgui_window_debug(void)
{
	if (g_show_demo_window)
		igShowDemoWindow(&g_show_demo_window);
}

static void	imgui_window_controls(t_rtv *rtv)
{
	igBegin("RT controls", 0, 0);
	igText("First sphere location");
	if (ig_drag_vector("center", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
		invalidate_sphere_vectors(rtv, rtv->spheres[0]);
	igEnd();
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

static void	loop_sdl(t_rtv *rtv)
{
	const GLuint	texture_id = create_texture(rtv);

	imgui_new_frame();
	imgui_window_texture(texture_id);
	imgui_window_debug();
	imgui_window_controls(rtv);
	imgui_render(rtv);
	delete_texture(texture_id);
}

int	loop_hook(t_rtv *rtv)
{
	loop_invalidate_position(rtv);
	loop_invalidate_rotation(rtv);
	loop_redraw(rtv);
	loop_render_debug(rtv);
	loop_sdl(rtv);
	loop_before_next_update(rtv);
	return (0);
}

void	loop_before_next_update(t_rtv *rtv)
{
	(void)rtv;
}
