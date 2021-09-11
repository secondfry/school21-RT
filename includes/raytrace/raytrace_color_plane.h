/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_color_plane.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:23:22 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 20:27:53 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_COLOR_PLANE_H
# define RAYTRACE_COLOR_PLANE_H

# include "defines.h"
# include "rtv.h"

void	check_texture_plane(\
	t_rtv *rtv, \
	const t_light_params *params, \
	t_intersection *intr \
);

#endif
