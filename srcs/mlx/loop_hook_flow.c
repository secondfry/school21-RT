/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:49:39 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/28 17:09:57 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"
#include <SDL_opengl.h>

// Our state
bool show_demo_window = true;
ImVec4 clear_color = {0.45f, 0.55f, 0.60f, 1.00f};

void	igImageDefaults(ImTextureID user_texture_id, const ImVec2 size)
{
	igImage(user_texture_id, size, (ImVec2){0, 0}, (ImVec2){1, 1}, (ImVec4){1, 1, 1, 1}, (ImVec4){0, 0, 0, 0});
}

bool	igDragVectorDefaults(const char *label, void *v)
{
	return igDragScalarN(label, ImGuiDataType_Double, v, 3, 0.05f, 0, 0, "%.3f", 0);
}

static void	loop_SDL(t_rtv *rtv)
{
	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, rtv->sdl->buffer);

	glBindTexture(GL_TEXTURE_2D, 0);



	ImGuiIO *io = igGetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	igNewFrame();

	bool wat = true;
	igBegin("OpenGL Texture Text", &wat, 0);
	igText("pointer = %p", texture_id);
	igText("size = %d x %d", WIDTH, HEIGHT);
	igImageDefaults((void*)(intptr_t)texture_id, (ImVec2) {WIDTH, HEIGHT});
	igEnd();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		igShowDemoWindow(&show_demo_window);

	igBegin("RT controls", 0, 0);
	igText("First sphere location");
	static float s0vCx;
	// ft_print_memory(&rtv->spheres[1].vectors[VCTR_SPHERE_C], sizeof(t_vector_4));
	if (igDragVectorDefaults("center", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
	{
		// vector_set_by_value(&rtv->spheres[0].vectors[VCTR_SPHERE_C], (t_vector_4){ s0vCx, 0, 0, 1 });
		invalidate_sphere_vectors(rtv, rtv->spheres[0]);
	}
		
	// if (igDragFloatDefaults("y", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
	// 	invalidate_sphere_vectors(rtv, rtv->spheres[0]);
	// if (igDragFloatDefaults("z", &rtv->spheres[0].vectors[VCTR_SPHERE_C].x))
	// 	invalidate_sphere_vectors(rtv, rtv->spheres[0]);
	igEnd();

	igRender();
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(rtv->sdl->window);

	glDeleteTextures(1, &texture_id);
}

int	loop_hook(t_rtv *rtv)
{
	loop_invalidate_position(rtv);
	loop_invalidate_rotation(rtv);
	loop_redraw(rtv);
	loop_render_debug(rtv);
	loop_SDL(rtv);
	loop_before_next_update(rtv);
	return (0);
}

void	loop_before_next_update(t_rtv *rtv)
{
	(void)rtv;
}
