/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_light.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:49:50 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:49:51 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_LIGHT_H
# define RAYTRACE_LIGHT_H

# include "defines.h"
# include "vector.h"
# include "intersection.h"

double	light(\
	t_rtv *rtv, \
	const t_light_params *params \
);

#endif
