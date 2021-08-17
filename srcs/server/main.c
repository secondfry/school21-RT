/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/17 21:19:10 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "init_rtv.h"
#include "server/main.h"

int	handle_message(zloop_t *loop, zsock_t *reader, void *arg)
{
	char	*id;
	t_rtv	*rtv;

	(void)loop;
	rtv = (t_rtv *)arg;
	id = zstr_recv(reader);
	if (handle_typed_message(reader, rtv, id))
		zstr_send(reader, "ACK");
	zstr_free(&id);
	return (0);
}

int	main(void)
{
	t_rtv	rtv;
	zsock_t	*responder;
	int		port;
	zloop_t	*reactor;

	ft_printf("zmq: %d, czmq: %d\n", ZMQ_VERSION, CZMQ_VERSION);
	responder = zsock_new(ZMQ_REP);
	port = zsock_bind(responder, "tcp://*:*[30000-]");
	if (port == -1)
	{
		ft_printf("Could not bind to port... Bailing!");
		zsock_destroy(&responder);
		return (1);
	}
	ft_printf("Server is up on port %d.\n", port);
	reactor = zloop_new();
	zloop_reader(reactor, responder, handle_message, &rtv);
	zloop_start(reactor);
	zloop_destroy(&reactor);
	zsock_destroy(&responder);
	return (0);
}
