/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/01 02:25:11 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>

int	main(void)
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
		return (1);
	}
	printf("Sending payload.\n");
	zstr_sendm(requester, "TYPE-INIT");
	zstr_send(requester, "This is some data for you.");
	data = zstr_recv(requester);
	printf("Received: %s", data);
	zstr_free(&data);
	zsock_destroy(&requester);
	return (0);
}
