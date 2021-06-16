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

int	loop_hook(t_wolf *wolf)
{
	loop_invalidate_position(wolf);
	loop_invalidate_rotation(wolf);
	loop_redraw(wolf);
	loop_render_debug(wolf);
	loop_before_next_update(wolf);
	return (0);
}

#ifdef MLX_LINUX

int	loop_destroy_hook(t_wolf *wolf)
{
	mlx_loop_end(wolf->mlx->mlx);
	clear_mlx(wolf->mlx);
	ft_putendl("Goodbye!");
	exit(0);
}

#else

int	loop_destroy_hook(t_wolf *wolf)
{
	clear_mlx(wolf->mlx);
	ft_putendl("Goodbye!");
	exit(0);
}

#endif

void	loop_before_next_update(t_wolf *wolf)
{
	mlx_do_sync(wolf->mlx->mlx);
}
