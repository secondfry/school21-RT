/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_handle_message.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:17:42 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 13:44:55 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "libft.h"
#include "init_rtv.h"
#include "parser.h"
#include "server/main.h"
#include "stb_image.h"

static t_byte	handle_init(t_rtv *rtv)
{
	FILE	*fp;
	char	filename[22];

	ft_bzero(filename, 22);
	fp = popen("mktemp /tmp/RT.server.XXXXXX", "r");
	fgets(filename, sizeof(filename), fp);
	pclose(fp);
	init_rtv(rtv);
	rtv->filename = ft_strdup(filename);
	return (1);
}

static t_byte	handle_scene(t_rtv *rtv, zsock_t *reader)
{
	char	*scene;
	int		fd;

	scene = zstr_recv(reader);
	ft_printf("Received: %s\n", scene);
	fd = open(rtv->filename, O_WRONLY | O_APPEND);
	if (fd < 3)
	{
		ft_printf("[%s] something wrong, bailing!\n", rtv->filename);
		exit(1);
	}
	write(fd, scene, ft_strlen(scene));
	close(fd);
	zstr_free(&scene);
	return (1);
}

static t_byte	handle_parse(t_rtv *rtv)
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

t_byte	handle_cleanup(t_rtv *rtv)
{
	stbi_image_free(rtv->textures[0].data);
	stbi_image_free(rtv->textures[1].data);
	ft_memdel((void **)&rtv->camera_rotation);
	ft_memdel((void **)&rtv->filename);
	return (1);
}

t_byte	handle_typed_message(zsock_t *reader, t_rtv *rtv, char *id)
{
	ft_printf("Received: %s\n", id);
	if (!ft_strcmp(id, "INIT"))
		return (handle_init(rtv));
	if (!ft_strcmp(id, "SCENE"))
		return (handle_scene(rtv, reader));
	if (!ft_strcmp(id, "PARSE"))
		return (handle_parse(rtv));
	if (!ft_strcmp(id, "RENDER"))
		return (handle_render(rtv, reader));
	if (!ft_strcmp(id, "CLEANUP"))
		return (handle_cleanup(rtv));
	return (1);
}
