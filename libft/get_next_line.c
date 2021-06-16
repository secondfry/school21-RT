/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:30:47 by oadhesiv          #+#    #+#             */
/*   Updated: 2019/06/05 19:06:07 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	decide_length(char buffer[BUFF_SIZE + 1], char *ptr)
{
	size_t	len;

	if (ptr)
		len = ptr - buffer;
	else
		len = ft_strlen(buffer);
	return (len);
}

int	drain(char **line, char buffer[BUFF_SIZE + 1], ssize_t *rlen)
{
	char			*ptr;
	size_t			len;

	ptr = ft_strchr(buffer, '\n');
	len = decide_length(buffer, ptr);
	*line = ft_strsub(buffer, 0, len);
	if (!*line)
		return (STATUS_ERR);
	ft_memmove(buffer, buffer + len + 1, *rlen - len + 1);
	*rlen -= len + 1;
	if (ptr)
		return (STATUS_READ);
	return (STATUS_EOF);
}

int	get_next_line(const int fd, char **line)
{
	static char		buffer[BUFF_SIZE + 1];
	static ssize_t	rlen;
	char			status;
	char			*tmp[2];

	if (!line)
		return (STATUS_ERR);
	status = drain(line, buffer, &rlen);
	if (status == STATUS_ERR || status == STATUS_READ)
		return (status);
	if (status == STATUS_EOF)
	{
		rlen = read(fd, buffer, BUFF_SIZE);
		if (rlen < 1)
			return ((rlen < 0) * STATUS_ERR + (rlen == 0) * STATUS_EOF);
		status = get_next_line(fd, &tmp[0]);
		tmp[1] = ft_strjoin(*line, tmp[0]);
		ft_memdel((void **)line);
		ft_memdel((void **)&tmp[0]);
		*line = tmp[1];
	}
	if (ft_strlen(*line))
		return (STATUS_READ);
	return (status);
}
