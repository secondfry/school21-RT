/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:13:34 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 19:00:52 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_rtv/stb.h"
#include "init_rtv/texture.h"
#include "SDL_opengl.h"
#include "libft.h"
#include "typedef_common.h"

void	load_texture(
	const char *filename,
	t_texture *ret
)
{
	ret->data = stbi_load(filename, &ret->width, &ret->height, NULL, 4);
	if (ret->data)
		ft_printf("Loaded texture from %s!\nwidth: %d\nheight: %d\n\n", \
			filename, ret->width, ret->height);
}
