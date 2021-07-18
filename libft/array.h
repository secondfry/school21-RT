/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:23:19 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/18 16:18:16 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include "libft.h"

typedef struct s_byte_array
{
	t_byte	*data;
	size_t	used;
	size_t	size;
}				t_byte_array;

t_byte_array	*byte_array_new(size_t len);
void			byte_array_destroy(t_byte_array *arr);
t_byte_array	*byte_array_resize(t_byte_array *arr, size_t len);
t_byte_array	*byte_array_add(t_byte_array *arr, t_byte data);
t_byte			byte_array_has(t_byte_array *arr, t_byte data);

typedef struct s_ptr_array
{
	void	**data;
	size_t	used;
	size_t	size;
}				t_ptr_array;

t_ptr_array		*ptr_array_new(size_t len);
void			ptr_array_destroy(t_ptr_array *arr);
t_ptr_array		*ptr_array_resize(t_ptr_array *arr, size_t len);
t_ptr_array		*ptr_array_add(t_ptr_array *arr, void *data);
t_byte			ptr_array_has(t_ptr_array *arr, void *data);

#endif
