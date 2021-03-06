/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:47:26 by oadhesiv          #+#    #+#             */
/*   Updated: 2019/04/23 15:49:09 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	if (size > SIZE_MAX - 1)
	{
		return ((void *)0);
	}
	return ((char *)ft_memalloc(size + 1));
}
