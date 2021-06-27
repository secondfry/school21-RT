/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:20:30 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/06 21:46:32 by oadhesiv         ###   ########.fr       */
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

float	vector_dot(t_vector_4 a, t_vector_4 b);
float	vector_length(t_vector_4 a);

t_vector_4	vector_normalize(t_vector_4 a);

#endif
