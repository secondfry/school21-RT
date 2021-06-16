/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:08:37 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 18:19:30 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mlx.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	ft_ptr_check(mlx->mlx, "[main] mlx_init errored.", 0);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
	{
		ft_mlx_destroy_display(mlx->mlx);
		ft_ptr_check(mlx->win, "[main] mlx_new_window errored.", 1, mlx->mlx);
	}
}

void	init_mlx_image(t_mlx *mlx)
{
	int	bits_per_pixel;
	int	size_line;
	int	endianess;

	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		ft_mlx_destroy_display(mlx->mlx);
		ft_ptr_check(mlx->img, "[main] mlx_new_image errored.", 1, mlx->mlx);
	}
	mlx->img_data = (int *)mlx_get_data_addr(\
		mlx->img, &bits_per_pixel, &size_line, &endianess);
	mlx->size_line_char = (size_t)size_line;
	mlx->size_line_int = (size_t)(size_line / 4);
}

void	clear_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_mlx_destroy_display(mlx->mlx);
	ft_memdel(&(mlx->mlx));
}

void	init_mlx_hooks(t_wolf *wolf)
{
	mlx_hook(\
		wolf->mlx->win, EVENT_KEY_PRESS, KEY_PRESS_MASK, loop_key_hook, wolf);
	mlx_loop_hook(wolf->mlx->mlx, loop_hook, wolf);
	init_mlx_hooks_platform(wolf);
}
