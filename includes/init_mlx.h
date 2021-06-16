/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:09:02 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/01/11 14:46:55 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_MLX_H
# define INIT_MLX_H

# include <stdlib.h>
# include <mlx.h>
# include "defines.h"
# include "loop_hook.h"
# include "clear_mlx.h"

void	init_mlx(t_mlx *mlx);
void	init_mlx_image(t_mlx *mlx);
void	clear_mlx(t_mlx *mlx);
void	init_mlx_hooks(t_wolf *wolf);
void	init_mlx_hooks_platform(t_wolf *wolf);

#endif
