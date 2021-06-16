#include "loop_hook.h"

void	loop_invalidate_position(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_INVALIDATE_POSITION))
		return ;
	rtv->player->wall.prev.x = \
		(int) rtv->player->pos.x - (int) rtv->player->pos.x % 64;
	rtv->player->wall.prev.y = \
		(int) rtv->player->pos.y - (int) rtv->player->pos.y % 64;
	rtv->player->wall.next.x = rtv->player->wall.prev.x + 64;
	rtv->player->wall.next.y = rtv->player->wall.prev.y + 64;
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
