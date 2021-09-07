/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_texture.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:37:44 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 19:38:18 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_TEXTURE_H
# define RAYTRACE_TEXTURE_H

# include "defines.h"
# include "rtv.h"

void	check_texture(\
	t_rtv *rtv, \
	const t_light_params *params, \
	t_intersection *intr \
);

#endif
