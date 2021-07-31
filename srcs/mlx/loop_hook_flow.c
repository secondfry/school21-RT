/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:49:39 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/01 02:38:14 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

int	loop_hook(t_rtv *rtv)
{
	loop_invalidate_position(rtv);
	loop_invalidate_rotation(rtv);
	loop_redraw(rtv);
	loop_render_debug(rtv);
	loop_before_next_update(rtv);
	return (0);
}

void	loop_before_next_update(t_rtv *rtv)
{
	mlx_do_sync(rtv->mlx->mlx);
}
