/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:20:30 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/06/28 21:14:59 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <math.h>
# include "defines.h"
# include "graceful.h"

t_vector_4	vector_new(float x, float y, float z, float w);
t_vector_4	vector_sub(t_vector_4 a, t_vector_4 b);
t_vector_4	vector_add(t_vector_4 a, t_vector_4 b);
t_vector_4	vector_mult(t_vector_4 a, float k);

float		vector_dot(t_vector_4 a, t_vector_4 b);
float		vector_length(t_vector_4 a);

t_vector_4	vector_normalize(t_vector_4 a);
t_vector_4	vector_cross(t_vector_4 a, t_vector_4 b);

void		vector_set(t_vector_4 *dst, t_vector_4 *src);

#endif
