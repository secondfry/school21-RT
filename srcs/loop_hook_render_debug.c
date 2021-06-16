#include "loop_hook.h"

static void	loop_render_debug_walls(t_wolf *wolf)
{
	char	*str;

	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 10, 35, 0xfffff, "Walls:");
	str = ft_itoa(wolf->player->wall.prev.x);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 90, 20, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(wolf->player->wall.prev.y);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 70, 30, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(wolf->player->wall.next.x);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 120, 40, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(wolf->player->wall.next.y);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 100, 50, 0xfffff, str);
	ft_memdel((void **)&str);
}

static void	loop_render_debug_angle(t_wolf *wolf)
{
	char	*str;

	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 10, 65, 0xfffff, "Angle:");
	str = ft_itoa(wolf->player->angle);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 70, 65, 0xfffff, str);
	ft_memdel((void **)&str);
}

static void	loop_render_debug_isaac(t_wolf *wolf)
{
	char	*str;

	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 10, 80, 0xfffff, "Isaac:");
	str = ft_itoa(wolf->player->pos.x);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 70, 80, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(wolf->player->pos.y);
	mlx_string_put(wolf->mlx->mlx, wolf->mlx->win, 120, 80, 0xfffff, str);
	ft_memdel((void **)&str);
}

void	loop_render_debug(t_wolf *wolf)
{
	loop_render_debug_walls(wolf);
	loop_render_debug_angle(wolf);
	loop_render_debug_isaac(wolf);
}
