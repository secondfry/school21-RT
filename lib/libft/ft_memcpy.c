/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:23:47 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/06 18:00:00 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_ulong			*dst_ulong;
	const t_ulong	*src_ulong;
	t_byte			*dst_byte;
	const t_byte	*src_byte;

	if (!dst || !src || !n)
		return (dst);
	dst_ulong = (t_ulong *)dst;
	src_ulong = (const t_ulong *)src;
	while (n > sizeof(long))
	{
		*dst_ulong++ = *src_ulong++;
		n -= sizeof(long);
	}
	dst_byte = (t_byte *)dst_ulong;
	src_byte = (const t_byte *)src_ulong;
	while (n--)
		*dst_byte++ = *src_byte++;
	return (dst);
}
