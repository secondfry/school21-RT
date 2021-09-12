/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:49:05 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:49:07 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_PLANE_H
# define INTERSECTION_PLANE_H

# include <math.h>
# include "libft.h"
# include "vector.h"
# include "defines.h"

t_intersection	intersection_plane_closest(\
	t_rtv *rtv, \
	t_intersect_params *params \
);

#endif
