/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_array_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secondfry <secondfry@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:19:20 by secondfry         #+#    #+#             */
/*   Updated: 2021/09/04 19:19:20 by secondfry        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "array.h"

t_ptr_array	*ptr_array_new(size_t len)
{
	t_ptr_array	*ret;

	len = len + sizeof(long) - len % sizeof(long);
	ret = (t_ptr_array *)malloc(sizeof(t_ptr_array));
	if (!ret)
		return ((void *)0);
	ret->size = len;
	ret->used = 0;
	ret->data = (void **)malloc(sizeof(void *) * len);
	if (!ret->data)
		ft_memdel((void **)&ret);
	return (ret);
}
