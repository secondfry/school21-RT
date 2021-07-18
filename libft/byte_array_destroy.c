/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_array_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:21:38 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/18 15:56:27 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array.h"

void	byte_array_destroy(t_byte_array *arr)
{
	if (!arr)
		return ;
	free(arr->data);
	free(arr);
}
