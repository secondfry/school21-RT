/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_redraw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:39:04 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/28 15:00:36 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hook.h"
#include "init_sdl.h"

static void	*run_parametrized(void *params)
{
	short	yc;
	short	xc;
	t_color	color;

	yc = ((t_params *)params)->ya;
	while (yc <= ((t_params *)params)->yb)
	{
		xc = ((t_params *)params)->xa;
		while (xc < ((t_params *)params)->xb)
		{
			color = process_pixel(((t_params *)params)->rtv, xc, yc);
			canvas_to_screen(((t_params *)params)->rtv, xc, yc, color);
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

static void	prepare_parellel_params(t_rtv *rtv, t_params *param)
{
	t_byte			line;
	short			line_start;
	short			line_end;
	static short	global_start = -1 * HEIGHT / 2;

	line = 0;
	while (line < 8)
	{
		line_start = global_start + line * HEIGHT / 8;
		line_end = global_start + (line + 1) * HEIGHT / 8;
		if (line_start == global_start)
			line_start = global_start + 1;
		param[line] = (t_params){\
			rtv, \
			line_start, \
			line_end, \
			-1 * WIDTH / 2, \
			WIDTH / 2 \
		};
		line++;
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
	void	*data;

	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	sdl_clear_texture(rtv->sdl);
	rtv->flags -= FLAG_REDRAW;
	SDL_LockTexture(rtv->sdl->texture, NULL, &data, &rtv->sdl->pitch);
	rtv->sdl->buffer = data;
	run_parallel(rtv);
	SDL_UnlockTexture(rtv->sdl->texture);
}
