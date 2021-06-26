#include "loop_hook.h"

void	loop_invalidate_position(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_INVALIDATE_POSITION))
		return ;
	rtv->flags -= FLAG_INVALIDATE_POSITION;
	rtv->flags |= FLAG_REDRAW;
}

void	loop_invalidate_rotation(t_rtv *rtv)
{
	t_quaterion rotator;

	if (!(rtv->flags & FLAG_INVALIDATE_ROTATION))
		return ;
	rtv->flags -= FLAG_INVALIDATE_ROTATION;
	rotator = quaternion_new(rtv->camera_angles[AYAW], rtv->camera_angles[AROLL], rtv->camera_angles[APITCH]);
	free(rtv->camera_rotation);
	rtv->camera_rotation = quaternion_to_matrix(rotator);
	free(rotator);
	rtv->flags |= FLAG_REDRAW;
}
