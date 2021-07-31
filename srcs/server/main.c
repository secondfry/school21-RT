/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/01 02:54:25 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "libft.h"

void	handle_scene(zsock_t *reader)
{
	char	*scene;

	scene = zstr_recv(reader);
	zstr_free(&scene);
}

void	handle_typed_message(zsock_t *reader, char *id)
{
	if (!ft_strcmp(id, "SCENE"))
		handle_scene(reader);
}

int	handle_message(zloop_t *loop, zsock_t *reader, void *arg)
{
	char	*id;

	(void)loop;
	(void)arg;
	id = zstr_recv(reader);
	handle_typed_message(reader, id);
	zstr_send(reader, "ACK");
	zstr_free(&id);
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
