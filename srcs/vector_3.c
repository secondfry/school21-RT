/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:34:26 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 19:34:48 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector_4	vector_uv(t_rtv *rtv, t_vector_4 input)
{
	const t_vector_4	modded = {
		fmod((input.x + rtv->textures[0].offset.x) * rtv->textures[0].scale.x, \
			rtv->textures[0].width),
		0.0,
		fmod((input.z + rtv->textures[0].offset.z) * rtv->textures[0].scale.z, \
			rtv->textures[0].height),
		0.0
	};
	const t_vector_4	output = {
		modded.x + (modded.x < 0) * rtv->textures[0].width,
		0.0,
		modded.z + (modded.z < 0) * rtv->textures[0].height,
		0.0
	};

	return (output);
}
