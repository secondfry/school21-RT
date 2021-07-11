#ifndef LIGHTS_H
# define LIGHTS_H

# include "typedef_common.h"

typedef struct s_plight
{
	t_vector_4	position;
	float		intensity;
	t_byte		traits;
}				t_plight;

typedef struct s_dlight
{
	t_vector_4	direction;
	float		intensity;
	t_byte		traits;
}				t_dlight;

#endif
