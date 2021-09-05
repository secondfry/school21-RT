/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_invalidate.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:17:03 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:18:00 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_HOOK_INVALIDATE_H
# define LOOP_HOOK_INVALIDATE_H

# include "rtv.h"
# include "figures.h"

void	invalidate_sphere_vectors(t_rtv *rtv, t_sphere sphere);
void	loop_invalidate_position(t_rtv *rtv);
void	loop_invalidate_rotation(t_rtv *rtv);

#endif
