/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 01:06:13 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/28 14:28:55 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <czmq.h>
#include "typedef_common.h"
#include "init_rtv.h"
#include "loop_hook.h"
#include "client/main.h"

void	run_cluster(t_rtv *rtv)
{
	cluster_request(rtv);
}

int	main(void)
{
	t_rtv	rtv;
	t_mlx	mlx;

	init_rtv(&rtv);
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	rtv.mlx = &mlx;
	init_mlx_hooks(&rtv);
	mlx_loop(mlx.mlx);
	return (0);
}
