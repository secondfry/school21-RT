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
	if (!(rtv->flags & FLAG_INVALIDATE_ROTATION))
		return ;
	rtv->flags -= FLAG_INVALIDATE_ROTATION;
	rtv->flags |= FLAG_REDRAW;
}
