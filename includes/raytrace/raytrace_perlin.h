/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_perlin.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:56:07 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/11 23:01:15 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_PERLIN_H
# define RAYTRACE_PERLIN_H

# define PERLIN_SIZE 32

typedef struct s_vector_2
{
	double	x;
	double	y;
}				t_vector_2;

double	perlin(double x, double y);
void	init_perlin(void);

#endif
