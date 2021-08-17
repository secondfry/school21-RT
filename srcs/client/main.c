/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/17 20:37:23 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "typedef_common.h"
#include "init_rtv.h"
#include "init_mlx.h"
#include "loop_hook.h"

#define BUFFER_SIZE 1048576

void	network_init(zsock_t **requester, int *status)
{
	printf("zmq: %d, czmq: %d\n", ZMQ_VERSION, CZMQ_VERSION);
	*requester = zsock_new(ZMQ_REQ);
	*status = zsock_connect(*requester, "tcp://localhost:30000");
	if (*status == -1)
	{
		printf("Could not connect to server... Bailing!");
		zsock_destroy(requester);
	}
}

void	network_send_init(zsock_t *requester)
{
	char	*data;

	zstr_send(requester, "INIT");
	data = zstr_recv(requester);
	printf("Received: %s\n", data);
	zstr_free(&data);
}

void	network_send_scene(zsock_t *requester)
{
	const int	fd = open("tests/scenes/full.oadyaml", O_RDONLY);
	char		*data;
	char		buffer[BUFFER_SIZE + 1];
	int			len;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	while ((len = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len] = 0;
		printf("Sending payload.\n");
		zstr_sendm(requester, "SCENE");
		zstr_send(requester, buffer);
		data = zstr_recv(requester);
		printf("Received: %s\n", data);
		zstr_free(&data);
	}
	close(fd);
}

void	network_request_parse(zsock_t *requester)
{
	char	*data;

	zstr_send(requester, "PARSE");
	data = zstr_recv(requester);
	printf("Received: %s\n", data);
	zstr_free(&data);
}

void	network_request_render(zsock_t *requester, t_rtv *rtv)
{
	char	*data;
	t_color	color;
	short	yc;
	short	xc;
	size_t	parts;

	zstr_send(requester, "RENDER");
	parts = 0;
	while (1)
	{
		data = zstr_recv(requester);
		if (!ft_strcmp(data, "ACK"))
		{
			zstr_free(&data);
			break;
		}
		color.red = data[0];
		zstr_free(&data);
		data = zstr_recv(requester);
		color.green = data[0];
		zstr_free(&data);
		data = zstr_recv(requester);
		color.blue = data[0];
		zstr_free(&data);
		data = zstr_recv(requester);
		yc = ft_atoi(data);
		zstr_free(&data);
		data = zstr_recv(requester);
		xc = ft_atoi(data);
		zstr_free(&data);
		canvas_to_screen(rtv, xc, yc, color);
		parts++;
	}
	printf("Received %zu parts.\n", parts);
}

void	cluster_request(t_rtv *rtv)
{
	zsock_t	*requester;
	int		status;

	network_init(&requester, &status);
	network_send_init(requester);
	network_send_scene(requester);
	network_request_parse(requester);
	network_request_render(requester, rtv);
	zsock_destroy(&requester);
}

void	run_cluster(t_rtv *rtv)
{
	cluster_request(rtv);
}

int	loop_key_hook(int keycode, t_rtv *rtv)
{
	(void)keycode;
	(void)rtv;
	return (0);
}

void	loop_redraw(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_REDRAW))
		return ;
	ft_bzero(rtv->mlx->img_data, rtv->mlx->size_line_char * HEIGHT);
	rtv->flags -= FLAG_REDRAW;
	run_cluster(rtv);
	mlx_put_image_to_window(\
		rtv->mlx->mlx, rtv->mlx->win, rtv->mlx->img, 0, 0);
}

void	loop_before_next_update(t_rtv *rtv)
{
	mlx_do_sync(rtv->mlx->mlx);
}

int	loop_hook(t_rtv *rtv)
{
	loop_redraw(rtv);
	loop_before_next_update(rtv);
	return (0);
}

int	main(void)
{
	t_rtv	rtv;
	t_mlx	mlx;

	init_rtv(&rtv);
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	rtv.mlx = &mlx;
	init_mlx_hooks(&rtv);
	mlx_loop(mlx.mlx);
	return (0);
}
