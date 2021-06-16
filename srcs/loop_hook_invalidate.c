#include "loop_hook.h"

void	loop_invalidate_position(t_wolf *wolf)
{
	if (!(wolf->flags & FLAG_INVALIDATE_POSITION))
		return ;
	wolf->player->wall.prev.x = \
		(int) wolf->player->pos.x - (int) wolf->player->pos.x % 64;
	wolf->player->wall.prev.y = \
		(int) wolf->player->pos.y - (int) wolf->player->pos.y % 64;
	wolf->player->wall.next.x = wolf->player->wall.prev.x + 64;
	wolf->player->wall.next.y = wolf->player->wall.prev.y + 64;
	wolf->flags -= FLAG_INVALIDATE_POSITION;
	wolf->flags |= FLAG_REDRAW;
}

void	loop_invalidate_rotation(t_wolf *wolf)
{
	if (!(wolf->flags & FLAG_INVALIDATE_ROTATION))
		return ;
	wolf->flags -= FLAG_INVALIDATE_ROTATION;
	wolf->flags |= FLAG_REDRAW;
}
