#include "init_mlx.h"

#if defined(MLX_LINUX)

void	init_mlx_hooks_platform(t_rtv *rtv)
{
	mlx_hook(rtv->mlx->win,
		EVENT_CLIENT_MESSAGE, STRUCTURE_NOTIFY_MASK, loop_destroy_hook, rtv);
}

#elif defined(MLX_MACOS_METAL) || defined(MLX_MACOS)

void	init_mlx_hooks_platform(t_rtv *rtv)
{
	mlx_hook(rtv->mlx->win,
		EVENT_DESTROY_NOTIFY, 0, loop_destroy_hook, rtv);
}

#endif
