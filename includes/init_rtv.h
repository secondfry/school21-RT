/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rtv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:48:10 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:48:12 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_RTV_H
# define INIT_RTV_H

# include "defines.h"
# include "vector.h"
# include "matrix_factory.h"
# include "color.h"

void	init_rtv_objects(t_rtv *rtv);
void	init_rtv_lights(t_rtv *rtv);
void	init_rtv(t_rtv *rtv);

#endif
