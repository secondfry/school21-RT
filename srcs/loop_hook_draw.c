#include "loop_hook.h"

static float	get_wall_height(t_rtv *rtv, float angle, float distance)
{
	float	dangle;
	float	multiplicator;
	float	distance_corrected;

	dangle = angle - rtv->player->angle;
	multiplicator = cosf(dangle * M_PI_F / 180);
	distance_corrected = distance * multiplicator;
	return (WALL_HEIGHT * rtv->projection_distance \
		/ distance_corrected / HEIGHT_COEF);
}

static t_byte	get_wall_variant(t_rtv *rtv, t_byte side)
{
	if (rtv->options & OPTION_ART)
	{
		if (side == TEX_SOUTH)
			return (TEX_ART_SOUTH);
		if (side == TEX_NORTH)
			return (TEX_ART_NORTH);
		if (side == TEX_WEST)
			return (TEX_ART_WEST);
		if (side == TEX_EAST)
			return (TEX_ART_EAST);
	}
	if (side == TEX_SOUTH)
		return (TEX_ISAAC_SOUTH);
	if (side == TEX_NORTH)
		return (TEX_ISAAC_NORTH);
	if (side == TEX_WEST)
		return (TEX_ISAAC_WEST);
	if (side == TEX_EAST)
		return (TEX_ISAAC_EAST);
	return (TEX_ERROR);
}

static t_byte	get_wall_idx(t_rtv *rtv, t_point point, _Bool isvert)
{
	if (rtv->player->pos.y < point.y && isvert == 0)
		return (get_wall_variant(rtv, TEX_SOUTH));
	if (rtv->player->pos.y > point.y && isvert == 0)
		return (get_wall_variant(rtv, TEX_NORTH));
	if (rtv->player->pos.x > point.x && isvert == 1)
		return (get_wall_variant(rtv, TEX_WEST));
	if (rtv->player->pos.x < point.x && isvert == 1)
		return (get_wall_variant(rtv, TEX_EAST));
	return (TEX_ERROR);
}

static void	draw_wall(t_rtv *rtv, t_point point, int texpos, _Bool isvert)
{
	short		start;
	short		end;
	short		row;
	t_ushort	pixel;

	start = (HEIGHT - rtv->wall_height) / 2;
	end = (HEIGHT + rtv->wall_height) / 2;
	if (rtv->player->pos.y < point.y && isvert == 0)
		texpos = 63 - texpos;
	if (rtv->player->pos.x > point.x && isvert == 1)
		texpos = 63 - texpos;
	row = start;
	if (row < 0)
		row = 0;
	while (row < end && row < HEIGHT)
	{
		pixel = (end - row - 1) * 64 / rtv->wall_height * 64 + texpos;
		rtv->mlx->img_data[row * rtv->mlx->size_line_int + rtv->column] = \
			rtv->texture \
				[get_wall_idx(rtv, point, isvert)] \
				[pixel];
		row++;
	}
}

void	draw(t_rtv *rtv, float angle, t_point dots[2], float distances[2])
{
	if (dots[0].x == 0 && dots[0].y == 0)
	{
		rtv->wall_height = get_wall_height(rtv, angle, distances[1]);
		draw_wall(rtv, dots[1], ((int)dots[1].y) % 64, 1);
	}
	else if (dots[1].x == 0 && dots[1].y == 0)
	{
		rtv->wall_height = get_wall_height(rtv, angle, distances[0]);
		draw_wall(rtv, dots[0], ((int)dots[0].x) % 64, 0);
	}
	else if (distances[0] > distances[1])
	{
		rtv->wall_height = get_wall_height(rtv, angle, distances[1]);
		draw_wall(rtv, dots[1], ((int)dots[1].y) % 64, 1);
	}
	else
	{
		rtv->wall_height = get_wall_height(rtv, angle, distances[0]);
		draw_wall(rtv, dots[0], ((int)dots[0].x) % 64, 0);
	}
}
