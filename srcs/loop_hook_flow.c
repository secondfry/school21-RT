/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:49:39 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 16:44:16 by oadhesiv         ###   ########.fr       */
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

#ifdef MLX_LINUX

int	loop_destroy_hook(t_rtv *rtv)
{
	mlx_loop_end(rtv->mlx->mlx);
	clear_mlx(rtv->mlx);
	ft_putendl("Goodbye!");
	exit(0);
}

#else

int	loop_destroy_hook(t_rtv *rtv)
{
	clear_mlx(rtv->mlx);
	ft_putendl("Goodbye!");
	exit(0);
}

#endif

void	loop_before_next_update(t_rtv *rtv)
{
	mlx_do_sync(rtv->mlx->mlx);
}
