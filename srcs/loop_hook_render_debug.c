#include "loop_hook.h"

static void	loop_render_debug_walls(t_rtv *rtv)
{
	char	*str;

	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 10, 35, 0xfffff, "Walls:");
	str = ft_itoa(rtv->player->wall.prev.x);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 90, 20, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(rtv->player->wall.prev.y);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 70, 30, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(rtv->player->wall.next.x);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 120, 40, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(rtv->player->wall.next.y);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 100, 50, 0xfffff, str);
	ft_memdel((void **)&str);
}

static void	loop_render_debug_angle(t_rtv *rtv)
{
	char	*str;

	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 10, 65, 0xfffff, "Angle:");
	str = ft_itoa(rtv->player->angle);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 70, 65, 0xfffff, str);
	ft_memdel((void **)&str);
}

static void	loop_render_debug_isaac(t_rtv *rtv)
{
	char	*str;

	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 10, 80, 0xfffff, "Isaac:");
	str = ft_itoa(rtv->player->pos.x);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 70, 80, 0xfffff, str);
	ft_memdel((void **)&str);
	str = ft_itoa(rtv->player->pos.y);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 120, 80, 0xfffff, str);
	ft_memdel((void **)&str);
}

void	loop_render_debug(t_rtv *rtv)
{
	loop_render_debug_walls(rtv);
	loop_render_debug_angle(rtv);
	loop_render_debug_isaac(rtv);
}
