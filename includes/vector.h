/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:20:30 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 19:34:45 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <math.h>
# include "defines.h"
# include "graceful.h"

t_vector_4	vector_new(double x, double y, double z, double w);
t_vector_4	vector_sub(t_vector_4 a, t_vector_4 b);
t_vector_4	vector_add(t_vector_4 a, t_vector_4 b);
t_vector_4	vector_mult(t_vector_4 a, double k);

double		vector_dot(t_vector_4 a, t_vector_4 b);
double		vector_length(t_vector_4 a);

t_vector_4	vector_normalize(t_vector_4 a);
t_vector_4	vector_cross(t_vector_4 a, t_vector_4 b);

void		vector_set(t_vector_4 *dst, t_vector_4 *src);
void		vector_set_by_value(t_vector_4 *dst, t_vector_4 src);

t_vector_4	vector_uv(t_rtv *rtv, t_vector_4 input);

#endif
