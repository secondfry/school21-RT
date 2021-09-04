/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_array_has.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secondfry <secondfry@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:19:29 by secondfry         #+#    #+#             */
/*   Updated: 2021/09/04 19:19:30 by secondfry        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_byte	ptr_array_has(t_ptr_array *arr, void *data)
{
	size_t	i;

	i = 0;
	while (i < arr->used)
	{
		if (arr->data[i] == data)
			return (1);
		i++;
	}
	return (0);
}
