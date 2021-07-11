#include "init_rtv.h"

static void	init_rtv_plights(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_PLIGHTS)
	{
		ft_memcpy(rtv->plights + i, &((t_plight){
			{0, 0, 0, 0}, \
			0, \
			0 \
		}), sizeof(t_plight));
		i++;
	}
}

static void	init_rtv_dlights(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_DLIGHTS)
	{
		ft_memcpy(rtv->dlights + i, &((t_dlight){
			{0, 0, 0, 0}, \
			0, \
			0 \
		}), sizeof(t_dlight));
		i++;
	}
}

static void	init_rtv_ambient(t_rtv *rtv)
{
	rtv->ambient = 0.0f;
}

void	init_rtv_lights(t_rtv *rtv)
{
	init_rtv_plights(rtv);
	init_rtv_dlights(rtv);
	init_rtv_ambient(rtv);
}
