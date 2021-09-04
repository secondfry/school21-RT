/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_array_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secondfry <secondfry@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:19:24 by secondfry         #+#    #+#             */
/*   Updated: 2021/09/04 19:19:25 by secondfry        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_ptr_array	*ptr_array_add(t_ptr_array *arr, void *data)
{
	if (arr->size == arr->used)
		arr = ptr_array_resize(arr, arr->size);
	arr->data[arr->used] = data;
	arr->used++;
	return (arr);
}
