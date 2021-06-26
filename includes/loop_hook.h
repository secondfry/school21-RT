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

# include <math.h>
# include "defines.h"
# include "init_mlx.h"
# include "color.h"
# include "vector.h"
# include "quaternion.h"
# include "matrix_utils.h"

int		loop_hook(t_rtv *rtv);
int		loop_destroy_hook(t_rtv *rtv);
void	loop_before_next_update(t_rtv *rtv);
void	loop_invalidate_position(t_rtv *rtv);
void	loop_invalidate_rotation(t_rtv *rtv);
void	loop_redraw(t_rtv *rtv);
void	draw(t_rtv *rtv);
void	loop_render_debug(t_rtv *rtv);
int		loop_key_hook(int keycode, t_rtv *rtv);

#endif
