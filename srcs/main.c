/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:52:15 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/28 15:50:09 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_defines(void)
{
	if ((WIDTH < 1 || WIDTH > 1920)
		|| (HEIGHT < 1 || HEIGHT > 1080)
	)
		graceful(ERR_INVALID_DEFINE, ERR_INVALID_DEFINE_MSG);
}


////////////////////////////////////////////////////////////////////////////////
// delete
#include <stdio.h>

void print_vector(t_vector_4 n) {
	printf("\tvector x: %f, y: %f, z: %f, w: %f\n", n.x, n.y, n.z, n.w);
}

void print_color(t_color c) {
	printf("\tcolor red: %d, green: %d, blue: %d\n", c.red, c.green, c.blue);
}

int check_sphere(t_sphere sph){
	int sum = 0;
	for (size_t j = 0; j < MAX_VECTORS_SPHERE; j++) {
			if (sph.vectors[j].x) sum++;
			if (sph.vectors[j].y) sum++;
			if (sph.vectors[j].z) sum++;
			if (sph.vectors[j].w) sum++;
	}
	if (sph.color.red) sum++;
	if (sph.color.green) sum++;
	if (sph.color.blue) sum++;
	
	if (sph.radius_squared) sum++;
	if (sph.specular) sum++;
	if (sph.traits) sum++;
	return sum;
}

void print_rtv(t_rtv *rtv)
{
	//print sphere 
	t_sphere *sph = rtv->spheres;
	int res;
	printf("SPHERES: max_spheres - %d pcs\n\n", MAX_SPHERES);
	for (size_t i = 0; i < MAX_SPHERES; i++) {
		if ((res = check_sphere(sph[i]))) {
			printf("Sphere number %zu: check emptyness: %d\n", i, res);
			for (size_t j = 0; j < MAX_VECTORS_SPHERE; j++) {
				print_vector(sph[i].vectors[j]);
				printf("\n");
			}
			print_color(sph[i].color);
			printf("\n");
			printf("\tRadius: %f\n\n\tSpecular: %f\n\n\tTraits: %d\n\n", sph[i].radius_squared, sph[i].specular, sph[i].traits);
			printf("----------------------------------------------------------------------\n");
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

/**
 *	Точка входа в приложение
 */
int	main(int argc, char **argv)
{
	t_rtv	rtv;
	t_mlx	mlx;

	check_defines();
	init_rtv(&rtv);
	parser(&rtv, argc, argv);
	print_rtv(&rtv); //delete this debug
	init_mlx(&mlx);
	init_mlx_image(&mlx);
	rtv.mlx = &mlx;
	init_mlx_hooks(&rtv);
	mlx_loop(mlx.mlx);
	return (0);
}
