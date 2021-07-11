#include "loop_hook.h"

static void	loop_render_debug_camera(t_rtv *rtv)
{
	char	*str;

	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 10, 20, 0xfff, "Camera | x:");
	str = ft_itoa(rtv->camera_position.x);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 130, 20, 0xfff, str);
	ft_memdel((void **)&str);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 10, 40, 0xfff, "       | y:");
	str = ft_itoa(rtv->camera_position.y);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 130, 40, 0xfff, str);
	ft_memdel((void **)&str);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 10, 60, 0xfff, "       | z:");
	str = ft_itoa(rtv->camera_position.z);
	mlx_string_put(rtv->mlx->mlx, rtv->mlx->win, 130, 60, 0xfff, str);
	ft_memdel((void **)&str);
}

void	loop_render_debug(t_rtv *rtv)
{
	loop_render_debug_camera(rtv);
}
