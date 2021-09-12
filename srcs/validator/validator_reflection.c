/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_reflection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:39:10 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 14:52:56 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_byte	try_process_reflection(
	t_rtv *rtv,
	t_byte type,
	t_byte idx,
	t_level *level
)
{
	if (level->type != LTYPE_LEAF || ft_strcmp(level->key, "reflection"))
		return (0);
	if (type == ISPHERE)
		rtv->spheres[idx].reflection = validate_reflection(level);
	if (type == ICONE)
		rtv->cones[idx].reflection = validate_reflection(level);
	if (type == ICYLINDER)
		rtv->cylinders[idx].reflection = validate_reflection(level);
	if (type == IPLANE)
		rtv->planes[idx].reflection = validate_reflection(level);
	return (1);
}
