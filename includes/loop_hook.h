/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:50:14 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 18:19:22 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_HOOK_H
# define LOOP_HOOK_H

# include "defines.h"
# include "init_mlx.h"
# include "intersection.h"

int		loop_hook(t_wolf *wolf);
int		loop_destroy_hook(t_wolf *wolf);
void	loop_before_next_update(t_wolf *wolf);
void	loop_invalidate_position(t_wolf *wolf);
void	loop_invalidate_rotation(t_wolf *wolf);
void	loop_redraw(t_wolf *wolf);
void	draw(t_wolf *wolf, float angle, t_point dots[2], float distances[2]);
void	loop_render_debug(t_wolf *wolf);
int		loop_key_hook(int keycode, t_wolf *wolf);

#endif
