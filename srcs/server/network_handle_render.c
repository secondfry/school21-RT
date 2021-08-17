/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_handle_render.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:28:39 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/17 22:00:38 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "typedef_common.h"
#include "init_rtv.h"
#include "raytrace.h"
#include "server/main.h"

static void	*run_parametrized(void *params)
{
	short	yc;
	short	xc;
	t_color	color;
	int		*data;
	size_t	offset;

	data = ((t_params *)params)->data;
	yc = ((t_params *)params)->ya;
	while (yc <= ((t_params *)params)->yb)
	{
		xc = ((t_params *)params)->xa;
		while (xc < ((t_params *)params)->xb)
		{
			color = process_pixel(((t_params *)params)->rtv, xc, yc);
			offset = (HEIGHT / 2 - yc) * WIDTH + WIDTH / 2 + xc;
			data[offset] = color_to_int(color);
			xc++;
		}
		yc++;
	}
	pthread_exit(NULL);
}

static void	prepare_parellel_params(t_rtv *rtv, int *data, t_params *param)
{
	t_byte			line;
	short			line_start;
	short			line_end;
	static short	global_start = -1 * HEIGHT / 2;

	line = 0;
	while (line < THREAD_COUNT)
	{
		line_start = global_start + line * HEIGHT / THREAD_COUNT;
		line_end = global_start + (line + 1) * HEIGHT / THREAD_COUNT;
		if (line_start == global_start)
			line_start = global_start + 1;
		param[line] = (t_params){\
			rtv, \
			data, \
			line_start, \
			line_end, \
			-1 * WIDTH / 2, \
			WIDTH / 2 \
		};
		line++;
	}
}

static void	send_one(zsock_t *reader, int *data, size_t ys, size_t xs)
{
	zstr_sendm(reader, (char [2]){data[ys * WIDTH + xs] >> 16 & 0xff, 0});
	zstr_sendm(reader, (char [2]){data[ys * WIDTH + xs] >> 8 & 0xff, 0});
	zstr_sendm(reader, (char [2]){data[ys * WIDTH + xs] >> 0 & 0xff, 0});
}

static void	send_all(zsock_t *reader, int *data)
{
	size_t	ys;
	size_t	xs;
	short	yc;
	short	xc;
	char	*tmp;

	ys = 0;
	while (ys < HEIGHT)
	{
		yc = HEIGHT / 2 - ys;
		xs = 0;
		while (xs < WIDTH)
		{
			xc = xs - WIDTH / 2;
			send_one(reader, data, ys, xs);
			tmp = ft_itoa(yc);
			zstr_sendm(reader, tmp);
			free(tmp);
			tmp = ft_itoa(xc);
			zstr_sendm(reader, tmp);
			free(tmp);
			xs++;
		}
		ys++;
	}
}

t_byte	handle_render(t_rtv *rtv, zsock_t *reader)
{
	int			*data;
	pthread_t	tid[THREAD_COUNT];
	t_params	param[THREAD_COUNT];
	t_byte		i;

	data = (int *)malloc(HEIGHT * WIDTH * sizeof(int));
	prepare_parellel_params(rtv, data, param);
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
	send_all(reader, data);
	free(data);
	zstr_send(reader, "ACK");
	return (0);
}

// t_byte	handle_render_single(t_rtv *rtv, zsock_t *reader)
// {
// 	short	yc;
// 	short	xc;
// 	char	*tmp;
// 	t_color	color;

// 	yc = -1 * HEIGHT / 2 + 1;
// 	while (yc <= HEIGHT / 2)
// 	{
// 		xc = -1 * WIDTH / 2;
// 		while (xc < WIDTH / 2)
// 		{
// 			color = process_pixel(rtv, xc, yc);
// 			zstr_sendm(reader, (char [2]){color.red, 0});
// 			zstr_sendm(reader, (char [2]){color.green, 0});
// 			zstr_sendm(reader, (char [2]){color.blue, 0});
// 			tmp = ft_itoa(yc);
// 			zstr_sendm(reader, tmp);
// 			free(tmp);
// 			tmp = ft_itoa(xc);
// 			zstr_sendm(reader, tmp);
// 			free(tmp);
// 			xc++;
// 		}
// 		yc++;
// 	}
// 	zstr_send(reader, "ACK");
// 	return (0);
// }
