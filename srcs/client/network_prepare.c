/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:02:53 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 13:37:24 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/network_prepare.h"

#include <czmq.h>
#include "client/network_render.h"

static void	network_init(zsock_t **requester, int *status)
{
	ft_printf("zmq: %d, czmq: %d\n", ZMQ_VERSION, CZMQ_VERSION);
	*requester = zsock_new(ZMQ_REQ);
	*status = zsock_connect(*requester, "tcp://localhost:30000");
	if (*status == -1)
	{
		ft_printf("Could not connect to server... Bailing!");
		zsock_destroy(requester);
	}
}

static void	network_send_init(zsock_t *requester)
{
	char	*data;

	zstr_send(requester, "INIT");
	data = zstr_recv(requester);
	ft_printf("Received: %s\n", data);
	zstr_free(&data);
}

static void	network_send_scene(zsock_t *requester)
{
	const int	fd = open("tests/scenes/full.oadyaml", O_RDONLY);
	char		*data;
	char		buffer[BUFFER_SIZE + 1];
	int			len;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (1)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buffer[len] = 0;
		ft_printf("Sending payload.\n");
		zstr_sendm(requester, "SCENE");
		zstr_send(requester, buffer);
		data = zstr_recv(requester);
		ft_printf("Received: %s\n", data);
		zstr_free(&data);
	}
	close(fd);
}

static void	network_request_parse(zsock_t *requester)
{
	char	*data;

	zstr_send(requester, "PARSE");
	data = zstr_recv(requester);
	ft_printf("Received: %s\n", data);
	zstr_free(&data);
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
	network_request_cleanup(requester);
	zsock_destroy(&requester);
}
