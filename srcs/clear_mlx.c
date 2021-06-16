#include "clear_mlx.h"

#ifdef MLX_LINUX

void	ft_mlx_destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}

#else

void	ft_mlx_destroy_display(void *mlx)
{
	(void)mlx;
}

#endif
