/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/11 21:32:26 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "libft.h"
#include "init_rtv.h"
#include "parser.h"

t_byte	handle_init(t_rtv *rtv)
{
	FILE	*fp;
	char	filename[22];

	ft_bzero(filename, 22);
	fp = popen("mktemp /tmp/RT.server.XXXXXX", "r");
	fgets(filename, sizeof(filename), fp);
	pclose(fp);
	init_rtv(rtv);
	free(rtv->filename);
	rtv->filename = ft_strdup(filename);
	return (1);
}

t_byte	handle_scene(t_rtv *rtv, zsock_t *reader)
{
	char	*scene;
	int		fd;

	scene = zstr_recv(reader);
	printf("Received: %s\n", scene);
	fd = open(rtv->filename, O_WRONLY | O_APPEND);
	if (fd < 3) { printf("[%s] pizdos\n", rtv->filename); exit(1); }
	write(fd, scene, ft_strlen(scene));
	close(fd);
	zstr_free(&scene);
	return (1);
}

t_byte	handle_parse(t_rtv *rtv)
{
	int		fd;
	int		len;
	t_level	*root;
	char	*memory;

	fd = open(rtv->filename, O_RDONLY);
	check(fd < 0, 1, ERR_PARSER_OPEN);
	len = read(fd, 0, 0);
	check(len < 0, 1, ERR_PARSER_READ);
	memory = 0;
	root = parse(fd, &memory);
	validate(rtv, root);
	free_parsed_struct(root);
	free(memory);
	return (1);
}

t_byte	handle_render(t_rtv *rtv)
{
	short	yc;
	short	xc;

	yc = -1 * HEIGHT / 2 + 1;
	while (yc <= HEIGHT / 2)
	{
		xc = -1 * WIDTH / 2;
		while (xc < WIDTH / 2)
		{
			process_pixel(rtv, xc, yc);
			xc++;
		}
		yc++;
	}
	return (0);
}

t_byte	handle_typed_message(zsock_t *reader, t_rtv *rtv, char *id)
{
	printf("Received: %s\n", id);
	if (!ft_strcmp(id, "INIT"))
		return (handle_init(rtv));
	if (!ft_strcmp(id, "SCENE"))
		return (handle_scene(rtv, reader));
	if (!ft_strcmp(id, "PARSE"))
		return (handle_parse(rtv));
	if (!ft_strcmp(id, "RENDER"))
		return (handle_render(rtv));
	return (1);
}

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
	zloop_reader(reactor, responder, handle_message, &rtv);
	zloop_start(reactor);
	zloop_destroy(&reactor);
	zsock_destroy(&responder);
	return (0);
}
