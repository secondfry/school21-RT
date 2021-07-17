/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:50:14 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/17 14:26:43 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_HOOK_H
# define LOOP_HOOK_H

# include <pthread.h>
# include <math.h>
# include "init_mlx.h"
# include "color.h"
# include "quaternion.h"
# include "matrix_utils.h"
# include "intersection.h"
# include "vector.h"
# include "raytrace.h"

typedef struct s_params {
	t_rtv	*rtv;
	short	ya;
	short	yb;
	short	xa;
	short	xb;
}				t_params;

# define THREAD_COUNT 8

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
