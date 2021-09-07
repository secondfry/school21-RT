/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actually_defines.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:34:42 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/07 17:26:55 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTUALLY_DEFINES_H
# define ACTUALLY_DEFINES_H

// actually without typedefs

# define WIDTH 768
# define HEIGHT 768
# define TITLE "RT"

# define M_PI_F 3.14159265358979323846264338327950288f
# define M_PI_2F 1.57079632679489661923132169163975144f

# define EPSILON 0.001f

# define ERR_INVALID_DEFINE	10

// these enums are here because they are "defines"

enum	e_flags
{
	FLAG_REDRAW = (1u << 0u),
	FLAG_INVALIDATE_POSITION = (1u << 1u),
	FLAG_INVALIDATE_ROTATION = (1u << 2u),
};

enum	e_traits
{
	TRAIT_EXISTS = (1u << 0u),
	TRAIT_NORMAL_SIN = (1u << 1u),
};

#endif
