/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_color_sphere.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:24:50 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 20:27:58 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_COLOR_SPHERE_H
# define RAYTRACE_COLOR_SPHERE_H

# include "defines.h"
# include "rtv.h"

void	check_texture_sphere(\
	t_rtv *rtv, \
	const t_light_params *params, \
	t_intersection *intr \
);

#endif
