/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls_spheres.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:59:42 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 21:09:36 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/window_controls_spheres.h"
#include "figures.h"
#include "rtv.h"
#include "imgui/controls.h"
#include "loop/loop_hook_invalidate.h"

const char		*g_sphere_labels[10] = {
	"Sphere #0",
	"Sphere #1",
	"Sphere #2",
	"Sphere #3",
	"Sphere #4",
	"Sphere #5",
	"Sphere #6",
	"Sphere #7",
	"Sphere #8",
	"Sphere #9",
};

float			g_color[MAX_SPHERES][3];
bool			g_enabled[MAX_SPHERES];
const t_byte	g_tex_min = 0;
const t_byte	g_tex_max = MAX_TEXTURES - 1;

static void	imgui_init_sphere_globals(t_rtv *rtv)
{
	static t_byte	once;
	static t_byte	i;

	if (once)
		return ;
	while (i < MAX_SPHERES)
	{
		g_color[i][0] = rtv->spheres[i].color.red / 255;
		g_color[i][1] = rtv->spheres[i].color.green / 255;
		g_color[i][2] = rtv->spheres[i].color.blue / 255;
		g_enabled[i] = rtv->spheres[i].traits & TRAIT_EXISTS;
		i++;
	}
	once = 1;
}

static void	imgui_sphere_enabled(t_rtv *rtv, t_byte idx)
{
	if (!igCheckbox("enabled", g_enabled + idx))
		return ;
	if (g_enabled[idx])
		rtv->spheres[idx].traits |= TRAIT_EXISTS;
	else
		rtv->spheres[idx].traits -= TRAIT_EXISTS;
	rtv->flags |= FLAG_REDRAW;
}

static void	imgui_sphere_normale_disruption(t_rtv *rtv, t_byte idx)
{
	static bool	normal_sin[MAX_SPHERES];

	if (!(igCheckbox("normale disruption", normal_sin + idx)))
		return ;
	if (normal_sin[idx])
		rtv->spheres[idx].traits |= TRAIT_NORMAL_SIN;
	else
		rtv->spheres[idx].traits -= TRAIT_NORMAL_SIN;
	rtv->flags |= FLAG_REDRAW;
}

static void	imgui_sphere_textured(t_rtv *rtv, t_byte idx)
{
	static bool	textured[MAX_SPHERES];

	if (igCheckbox("textured", textured + idx))
	{
		if (textured[idx])
			rtv->spheres[idx].traits |= TRAIT_TEXTURED;
		else
			rtv->spheres[idx].traits -= TRAIT_TEXTURED;
		rtv->flags |= FLAG_REDRAW;
	}
	if (igSliderScalar("texture_id", ImGuiDataType_U8, \
		&rtv->spheres[idx].texture_id, &g_tex_min, &g_tex_max, "%d", 0) \
	)
		rtv->flags |= FLAG_REDRAW;
}

static void	imgui_sphere_color_checkerboard(t_rtv *rtv, t_byte idx)
{
	static bool	checkerboard[MAX_SPHERES];

	if (!(igCheckbox("color disruption: checkboard", checkerboard + idx)))
		return ;
	if (checkerboard[idx])
		rtv->spheres[idx].traits |= TRAIT_CHECKERBOARD;
	else
		rtv->spheres[idx].traits -= TRAIT_CHECKERBOARD;
	rtv->flags |= FLAG_REDRAW;
}

static void	imgui_sphere_local_checkboxes(t_rtv *rtv, t_byte idx)
{
	imgui_sphere_normale_disruption(rtv, idx);
	imgui_sphere_textured(rtv, idx);
	imgui_sphere_color_checkerboard(rtv, idx);
}

static void	imgui_sphere_group(t_rtv *rtv, t_byte idx)
{
	if (!ig_group_default(g_sphere_labels[idx], !idx))
		return ;
	igPushID_Str(g_sphere_labels[idx]);
	if (ig_drag_vector("vec_c", &rtv->spheres[idx].vectors[VCTR_SPHERE_C].x))
		invalidate_sphere_vectors(rtv, rtv->spheres[idx]);
	if (ig_drag_double("radius^2", &rtv->spheres[idx].radius_squared))
		rtv->flags |= FLAG_REDRAW;
	if (ig_drag_double("specular", &rtv->spheres[idx].specular))
		rtv->flags |= FLAG_REDRAW;
	if (igColorEdit3("color", g_color[idx], 0))
	{
		rtv->spheres[idx].color = (t_color){g_color[idx][0] * 255, \
			g_color[idx][1] * 255, g_color[idx][2] * 255};
		rtv->flags |= FLAG_REDRAW;
	}
	imgui_sphere_enabled(rtv, idx);
	imgui_sphere_local_checkboxes(rtv, idx);
	igPopID();
}

void	imgui_spheres_group(t_rtv *rtv)
{
	t_byte		i;

	imgui_init_sphere_globals(rtv);
	if (!ig_group_top_default("Spheres"))
		return ;
	igPushID_Str("Spheres");
	i = 0;
	while (i < MAX_SPHERES)
	{
		imgui_sphere_group(rtv, i);
		i++;
	}
	igPopID();
}
