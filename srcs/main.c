/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 18:18:51 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"

void	init_player(t_player *player)
{
	player->pos.x = 3 * 32;
	player->pos.y = 3 * 32;
	player->angle = 135.0f;
}

void	init_rtv(t_rtv *rtv)
{
	rtv->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	rtv->projection_distance = WIDTH / 2 / tanf(FOV / 2 * M_PI_F / 180);
}

void	check_defines(void)
{
	if (FOV < 1 || FOV > 360)
		error_exit(ERR_INVALID_DEFINE);
	if (WIDTH < 240 || WIDTH > 1920)
		error_exit(ERR_INVALID_DEFINE);
	if (HEIGHT < 240 || HEIGHT > 1080)
		error_exit(ERR_INVALID_DEFINE);
	if (HEIGHT_COEF < 0.1 || HEIGHT_COEF > 4)
		error_exit(ERR_INVALID_DEFINE);
}

int	main(int argc, char **argv)
{
	t_rtv		rtv;
	t_mlx		mlx;
	t_player	player;
	int			fd;

	check_defines();
	parser(&rtv, fd);
	init_player(&player);
	rtv.player = &player;
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	rtv.mlx = &mlx;
	init_rtv(&rtv);
	init_textures(&rtv);
	init_mlx_hooks(&rtv);
	mlx_loop(mlx.mlx);
	return (0);
}
