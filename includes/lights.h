#ifndef LIGHTS_H
# define LIGHTS_H

# include "typedef_common.h"

typedef struct s_plight
{
	t_vector_4	position;
	double		intensity;
	t_byte		traits;
}				t_plight;

typedef struct s_dlight
{
	t_vector_4	direction;
	double		intensity;
	t_byte		traits;
}				t_dlight;

#endif
