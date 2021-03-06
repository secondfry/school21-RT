/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:48:21 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:48:23 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "defines.h"
# include "intersection_plane.h"
# include "intersection_sphere.h"
# include "intersection_cylinder.h"
# include "intersection_cone.h"

t_intersection	intersection_closest(t_rtv *rtv, t_intersect_params *params);

#endif
