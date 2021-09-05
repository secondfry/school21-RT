/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_clear_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 15:23:31 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:24:14 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl/sdl_clear_texture.h"

#include "actually_defines.h"
#include "sdl_defines.h"
#include "libft.h"

void	sdl_clear_texture(t_sdl *sdl)
{
	ft_bzero(sdl->buffer, WIDTH * HEIGHT * 4);
}
