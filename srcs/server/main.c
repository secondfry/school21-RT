/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/01 02:06:31 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>

int	handle_message(zloop_t *loop, zsock_t *reader, void *arg)
{
	char	*id;
	char	*data;

	(void)loop;
	(void)arg;
	zstr_recvx(reader, &id, &data);
	printf("%s: %s\n", id, data);
	zstr_free(&id);
	zstr_free(&data);
	return (0);
}

int	main(void)
{
	zsock_t	*responder;
	int		port;
	zloop_t	*reactor;

	printf("zmq: %d, czmq: %d\n", ZMQ_VERSION, CZMQ_VERSION);
	responder = zsock_new(ZMQ_REP);
	port = zsock_bind(responder, "tcp://*:*[30000-]");
	if (port == -1)
	{
		printf("Could not bind to port... Bailing!");
		zsock_destroy(&responder);
		return (1);
	}
	printf("Server is up on port %d.\n", port);
	reactor = zloop_new();
	zloop_reader(reactor, responder, handle_message, NULL);
	zloop_start(reactor);
	zloop_destroy(&reactor);
	zsock_destroy(&responder);
	return (0);
}
