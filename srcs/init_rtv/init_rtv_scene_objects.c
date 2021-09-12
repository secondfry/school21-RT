/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rtv_scene_objects.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:31:51 by hdean             #+#    #+#             */
/*   Updated: 2021/09/12 13:31:53 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_rtv.h"

static void	init_rtv_spheres(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_SPHERES)
	{
		ft_memcpy(rtv->spheres + i, &((t_sphere){
			{{0, 0, 0, 1}, {0, 0, 0, 0}}, \
			{0, 0, 0}, \
			1.0, \
			-1.0, \
			0, \
			0, \
			0, \
		}), sizeof(t_sphere));
		i++;
	}
}

static void	init_rtv_planes(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_PLANES)
	{
		ft_memcpy(rtv->planes + i, &((t_plane){
			{0, -1, 0, 1}, \
			{0, 1, 0, 0}, \
			{0, 0, 0}, \
			-1, \
			0, \
			0 \
		}), sizeof(t_plane));
		i++;
	}
	ft_memcpy(&rtv->slice, &((t_plane){
		{0.0, 0.0, 3.0, 1.0}, \
		{0.0, 3.0, 2.0, 0.0}, \
		{0, 0, 0}, \
		-1, \
		0, \
		0 \
	}), sizeof(t_plane));
}

static void	init_rtv_cylinders(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_CYLINDERS)
	{
		ft_memcpy(rtv->cylinders + i, &((t_cylinder){
			{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, \
			{0, 0, 0}, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_cylinder));
		i++;
	}
}

static void	init_rtv_cones(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_CONES)
	{
		ft_memcpy(rtv->cones + i, &((t_cone){
			{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, \
			{0, 0, 0}, \
			0, \
			0, \
			0, \
			0, \
			0, \
			0 \
		}), sizeof(t_cone));
		i++;
	}
}

void	init_rtv_objects(t_rtv *rtv)
{
	init_rtv_spheres(rtv);
	init_rtv_planes(rtv);
	init_rtv_cylinders(rtv);
	init_rtv_cones(rtv);
}
