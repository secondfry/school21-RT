/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:36:16 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 20:41:13 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace/raytrace_texture.h"
#include "raytrace/raytrace_color_plane.h"
#include "raytrace/raytrace_color_sphere.h"

void	check_texture(
	t_rtv *rtv,
	const t_light_params *params,
	t_intersection *intr
)
{
	if (intr->type == IPLANE)
		return (check_texture_plane(rtv, params, intr));
	if (intr->type == ISPHERE)
		return (check_color_sphere(rtv, params, intr));
}
