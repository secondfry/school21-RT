/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:05:36 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/11 21:05:37 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_parsed_struct(t_level *root)
{
	size_t	i;

	if (root->type == LTYPE_LEAF || root->type == LTYPE_LIST_LEAF)
	{
		free(root->key);
		free(root->value);
		free(root);
		return ;
	}
	if (root->type == LTYPE_NODE || root->type == LTYPE_LIST_NODE)
	{
		free(root->key);
		i = 0;
		while (i < root->data->used)
		{
			free_parsed_struct(root->data->data[i]);
			i++;
		}
		ptr_array_destroy(root->data);
		free(root);
	}
}
