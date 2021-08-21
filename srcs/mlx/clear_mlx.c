#include "clear_mlx.h"

#ifdef MLX_LINUX

void	ft_mlx_destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}

void	ft_mlx_destroy(void *mlx)
{
	ft_memdel(&mlx);
}

#else

void	ft_mlx_destroy_display(void *mlx)
{
	(void)mlx;
}

void	ft_mlx_destroy(void *mlx)
{
	(void)mlx;
}

#endif
