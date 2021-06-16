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

void	init_wolf(t_wolf *wolf)
{
	wolf->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	wolf->projection_distance = WIDTH / 2 / tanf(FOV / 2 * M_PI_F / 180);
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

int	check_args(int argc, char **argv)
{
	int	fd;
	int	res;

	if (argc != 2)
	{
		ft_putendl("\nUsage: \n$ ./wolf3d maps/map\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 3)
		error_exit(ERR_OPEN);
	res = read(fd, NULL, 0);
	if (res != 0)
		error_exit(ERR_READ);
	return (fd);
}

int	main(int argc, char **argv)
{
	t_wolf		wolf;
	t_mlx		mlx;
	t_player	player;
	int			fd;

	check_defines();
	fd = check_args(argc, argv);
	parser(&wolf, fd);
	init_player(&player);
	wolf.player = &player;
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	wolf.mlx = &mlx;
	init_wolf(&wolf);
	init_textures(&wolf);
	init_mlx_hooks(&wolf);
	mlx_loop(mlx.mlx);
	return (0);
}
