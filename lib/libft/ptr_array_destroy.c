/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_array_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:21:38 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/18 16:18:04 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "array.h"

void	ptr_array_destroy(t_ptr_array *arr)
{
	if (!arr)
		return ;
	free(arr->data);
	free(arr);
}
