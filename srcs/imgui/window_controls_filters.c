/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls_filters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 00:22:20 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 00:24:37 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgui/window_controls_filters.h"
#include "rtv.h"
#include "libft.h"
#include "filter.h"
#include "imgui/controls.h"

void	imgui_filters_group(t_rtv *rtv)
{
	const t_byte		fil_min = 0;
	const t_byte		fil_max = MAX_FILTER - 1;
	const static char	*filters[MAX_FILTER] = {
		"None",
		"Grayscale",
		"Sepia",
		"Invert",
		"Cartoon effect",
	};

	if (!ig_group_top_default("Filters"))
		return ;
	igPushID_Str("Filters");
	if (igSliderScalar("filter", ImGuiDataType_U8, \
		&rtv->filter, &fil_min, &fil_max, filters[rtv->filter], 0) \
	)
		rtv->flags |= FLAG_REDRAW;
	igPopID();
}
