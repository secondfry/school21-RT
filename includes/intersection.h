/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:05:06 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 16:07:13 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include <math.h>
# include "defines.h"

t_point	intersection_horizontal(t_rtv *rtv, float angle, float wall_y);
t_point	intersection_vertical(t_rtv *rtv, float angle, float wall_x);

#endif
