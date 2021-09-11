/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_sphere_uv.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:20:17 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 23:30:09 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_SPHERE_UV_H
# define RAYTRACE_SPHERE_UV_H

# include "defines.h"
# include "rtv.h"

void	get_uv_sphere(\
	t_rtv *rtv, \
	const t_light_params *params, \
	t_intersection *intr, \
	double uv[2] \
);

#endif
