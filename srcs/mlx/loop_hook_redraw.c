/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_redraw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:39:04 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/18 19:57:22 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"

static void	*run_parametrized(void *params)
{
	short	yc;
	short	xc;

	yc = ((t_params *)params)->ya;
	while (yc <= ((t_params *)params)->yb)
	{
		xc = ((t_params *)params)->xa;
		while (xc < ((t_params *)params)->xb)
		{
			process_pixel(((t_params *)params)->rtv, xc, yc);
			xc++;
		}
		yc++;
	}
	pthread_exit(NULL);
}

// static void	run_single(t_rtv *rtv)
// {
// 	short	yc;
// 	short	xc;

// 	yc = -1 * HEIGHT / 2 + 1;
// 	while (yc <= HEIGHT / 2)
// 	{
// 		xc = -1 * WIDTH / 2;
// 		while (xc < WIDTH / 2)
// 		{
// 			process_pixel(rtv, xc, yc);
// 			xc++;
// 		}
// 		yc++;
// 	}
// }

static short	get_y_start(t_byte y)
{
	static short	ya = -1 * HEIGHT / 2;

	if (y == 0)
		return (ya + 1);
	return (ya + y * HEIGHT / 2);
}

static void	prepare_parellel_params(t_rtv *rtv, t_params *param)
{
	t_byte			y;
	t_byte			x;
	short			yf;
	static short	ya = -1 * HEIGHT / 2;
	static short	xa = -1 * WIDTH / 2;

	y = 0;
	while (y < 2)
	{
		x = 0;
		yf = get_y_start(y);
		while (x < 4)
		{
			param[y * 4 + x] = (t_params){\
				rtv, \
				yf, \
				ya + (y + 1) * HEIGHT / 2, \
				xa + x * WIDTH / 4, \
				xa + (x + 1) * WIDTH / 4 \
			};
			x++;
		}
		y++;
	}
}

static void	run_parallel(t_rtv *rtv)
{
	pthread_t	tid[THREAD_COUNT];
	t_params	param[THREAD_COUNT];
	t_byte		i;

	prepare_parellel_params(rtv, param);
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_create(&tid[i], NULL, run_parametrized, &param[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

void	loop_redraw(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	ft_bzero(rtv->mlx->img_data, rtv->mlx->size_line_char * HEIGHT);
	rtv->flags -= FLAG_REDRAW;
	run_parallel(rtv);
	mlx_put_image_to_window(\
		rtv->mlx->mlx, rtv->mlx->win, rtv->mlx->img, 0, 0);
}
