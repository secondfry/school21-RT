#ifndef LIGHTS_HPP
# define LIGHTS_HPP

# include "typedef_common.h"

typedef struct s_plight
{
	t_vector_4	position;
	float		intensity;
	t_byte		traits;

	s_plight() : position{ 0.f, 0.f, 0.f, 1.f } {}
}				t_plight;

typedef struct	s_dlight
{
	t_vector_4	direction;
	float		intensity;
	t_byte		traits;

	s_dlight() : direction{ -1.f, -1.f, -1.f, 0.f } {}
}				t_dlight;

#endif
