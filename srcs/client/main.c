/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/01 03:27:23 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "typedef_common.h"
#include "init_rtv.h"
#include "init_mlx.h"

#define BUFFER_SIZE 10

void	cluster_request(void)
{
	zsock_t	*requester;
	int		status;
	char	*data;

	printf("zmq: %d, czmq: %d\n", ZMQ_VERSION, CZMQ_VERSION);
	requester = zsock_new(ZMQ_REQ);
	status = zsock_connect(requester, "tcp://localhost:30000");
	if (status == -1)
	{
		printf("Could not connect to server... Bailing!");
		zsock_destroy(&requester);
	}
	zstr_send(requester, "INIT");
	data = zstr_recv(requester);
	printf("Received: %s\n", data);
	zstr_free(&data);
	int fd = open("tests/scenes/full.oadyaml", O_RDONLY);
	char buffer[BUFFER_SIZE + 1];
	ft_bzero(buffer, BUFFER_SIZE + 1);
	int len;
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
	zsock_destroy(&requester);
}

void	run_cluster(t_rtv *rtv)
{
	// char	*data;

	(void)rtv;
	cluster_request();
	// ft_strcpy((char *)rtv->mlx->img_data, data);
	// zstr_free(&data);
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
