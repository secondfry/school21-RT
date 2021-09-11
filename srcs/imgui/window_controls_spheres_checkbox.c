/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls_spheres_checkbox.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 21:19:03 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 22:11:14 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/window_controls_spheres_checkbox.h"
#include "actually_defines.h"
#include "rtv.h"

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
	static bool			textured[MAX_SPHERES];
	const static t_byte	tex_min = 0;
	const static t_byte	tex_max = MAX_TEXTURES - 1;

	if (igCheckbox("textured", textured + idx))
	{
		if (textured[idx])
			rtv->spheres[idx].traits |= TRAIT_TEXTURED;
		else
			rtv->spheres[idx].traits -= TRAIT_TEXTURED;
		rtv->flags |= FLAG_REDRAW;
	}
	if (igSliderScalar("texture_id", ImGuiDataType_U8, \
		&rtv->spheres[idx].texture_id, &tex_min, &tex_max, "%d", 0) \
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

static void	imgui_sphere_color_sin(t_rtv *rtv, t_byte idx)
{
	static bool	sin[MAX_SPHERES];

	if (!(igCheckbox("color disruption: complicated", sin + idx)))
		return ;
	if (sin[idx])
		rtv->spheres[idx].traits |= TRAIT_COLOR_COMPLICATED;
	else
		rtv->spheres[idx].traits -= TRAIT_COLOR_COMPLICATED;
	rtv->flags |= FLAG_REDRAW;
}

void	imgui_sphere_local_checkboxes(t_rtv *rtv, t_byte idx)
{
	imgui_sphere_normale_disruption(rtv, idx);
	imgui_sphere_textured(rtv, idx);
	imgui_sphere_color_checkerboard(rtv, idx);
	imgui_sphere_color_sin(rtv, idx);
}
