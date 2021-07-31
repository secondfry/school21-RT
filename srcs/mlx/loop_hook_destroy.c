#include "loop_hook.h"

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
