/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:49:31 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:49:33 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_H
# define NORMAL_H

# include "defines.h"
# include "vector.h"

t_vector_4	find_normal(\
	t_rtv *rtv, \
	t_intersection *intr, \
	const t_light_params *params \
);

#endif
