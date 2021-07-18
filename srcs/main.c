/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarolei <pcarolei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/18 09:04:03 by pcarolei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_defines(void)
{
	if ((WIDTH < 1 || WIDTH > 1920)
		|| (HEIGHT < 1 || HEIGHT > 1080)
	)
		graceful(ERR_INVALID_DEFINE, ERR_INVALID_DEFINE_MSG);
}

/**
 *	Точка входа в приложение
 */
int	main(int argc, char **argv)
{
	t_rtv	rtv;
	t_mlx	mlx;

	check_defines();
	init_rtv(&rtv);
	parser(&rtv, argc, argv);
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	rtv.mlx = &mlx;
	init_mlx_hooks(&rtv);
	mlx_loop(mlx.mlx);
	return (0);
}
