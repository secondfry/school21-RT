/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:03:47 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:48:33 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "libft.h"
#include "rtv.h"
#include "loop_hook.h"

static t_byte	receive_color(zsock_t *requester, t_color *color)
{
	char	*data;

	data = zstr_recv(requester);
	if (!ft_strcmp(data, "ACK"))
	{
		zstr_free(&data);
		return (1);
	}
	color->red = data[0];
	zstr_free(&data);
	data = zstr_recv(requester);
	color->green = data[0];
	zstr_free(&data);
	data = zstr_recv(requester);
	color->blue = data[0];
	zstr_free(&data);
	return (0);
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
		if (receive_color(requester, &color))
			break ;
		data = zstr_recv(requester);
		yc = ft_atoi(data);
		zstr_free(&data);
		data = zstr_recv(requester);
		xc = ft_atoi(data);
		zstr_free(&data);
		canvas_to_screen(rtv, xc, yc, color);
		parts++;
	}
	ft_printf("Received %zu parts.\n", parts);
}
