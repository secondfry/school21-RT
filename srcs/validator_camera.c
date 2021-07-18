#include "parser.h"

t_byte	validate_camera(t_rtv *rtv, t_level *root)
{
	vector_set_by_value(&rtv->camera_position, get_vector(root));
	return (1);
}
