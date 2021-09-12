/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:39:10 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:42:54 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_byte	try_process_reflection(t_rtv *rtv, t_byte idx, t_level *level)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "reflection"))
		return (0);
	rtv->cones[idx].reflection = validate_reflection(level);
	return (1);
}
