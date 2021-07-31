#include "init_rtv.h"

static void	init_rtv_scene(t_rtv *rtv)
{
	init_rtv_objects(rtv);
	init_rtv_lights(rtv);
}

static void	init_rtv_common(t_rtv *rtv)
{
	rtv->flags = FLAG_INVALIDATE_POSITION | FLAG_INVALIDATE_ROTATION
		| FLAG_REDRAW;
	ft_memcpy(
		(void *)&rtv->camera_position, \
		&((t_vector_4){0.f, 0.f, -21.f, 1.f}), \
		sizeof(t_vector_4) \
	);
	vector_set_by_value(&rtv->camera_angles, vector_new(0, 0, 0, 0));
	rtv->camera_rotation = matrix_new_identity();
}

void	init_rtv(t_rtv *rtv)
{
	init_rtv_common(rtv);
	init_rtv_scene(rtv);
}
