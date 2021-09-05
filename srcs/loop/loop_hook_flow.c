/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:49:39 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 15:16:22 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"
#include "loop/loop_hook_invalidate.h"
#include "loop/loop_sdl.h"

int	loop_hook(t_rtv *rtv)
{
	loop_invalidate_position(rtv);
	loop_invalidate_rotation(rtv);
	loop_redraw(rtv);
	loop_sdl(rtv);
	return (0);
}
