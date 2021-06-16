#include "loop_hook.h"

static float	get_wall_height(t_wolf *wolf, float angle, float distance)
{
	float	dangle;
	float	multiplicator;
	float	distance_corrected;

	dangle = angle - wolf->player->angle;
	multiplicator = cosf(dangle * M_PI_F / 180);
	distance_corrected = distance * multiplicator;
	return (WALL_HEIGHT * wolf->projection_distance \
		/ distance_corrected / HEIGHT_COEF);
}

static t_byte	get_wall_variant(t_wolf *wolf, t_byte side)
{
	if (wolf->options & OPTION_ART)
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

static t_byte	get_wall_idx(t_wolf *wolf, t_point point, _Bool isvert)
{
	if (wolf->player->pos.y < point.y && isvert == 0)
		return (get_wall_variant(wolf, TEX_SOUTH));
	if (wolf->player->pos.y > point.y && isvert == 0)
		return (get_wall_variant(wolf, TEX_NORTH));
	if (wolf->player->pos.x > point.x && isvert == 1)
		return (get_wall_variant(wolf, TEX_WEST));
	if (wolf->player->pos.x < point.x && isvert == 1)
		return (get_wall_variant(wolf, TEX_EAST));
	return (TEX_ERROR);
}

static void	draw_wall(t_wolf *wolf, t_point point, int texpos, _Bool isvert)
{
	short		start;
	short		end;
	short		row;
	t_ushort	pixel;

	start = (HEIGHT - wolf->wall_height) / 2;
	end = (HEIGHT + wolf->wall_height) / 2;
	if (wolf->player->pos.y < point.y && isvert == 0)
		texpos = 63 - texpos;
	if (wolf->player->pos.x > point.x && isvert == 1)
		texpos = 63 - texpos;
	row = start;
	if (row < 0)
		row = 0;
	while (row < end && row < HEIGHT)
	{
		pixel = (end - row - 1) * 64 / wolf->wall_height * 64 + texpos;
		wolf->mlx->img_data[row * wolf->mlx->size_line_int + wolf->column] = \
			wolf->texture \
				[get_wall_idx(wolf, point, isvert)] \
				[pixel];
		row++;
	}
}

void	draw(t_wolf *wolf, float angle, t_point dots[2], float distances[2])
{
	if (dots[0].x == 0 && dots[0].y == 0)
	{
		wolf->wall_height = get_wall_height(wolf, angle, distances[1]);
		draw_wall(wolf, dots[1], ((int)dots[1].y) % 64, 1);
	}
	else if (dots[1].x == 0 && dots[1].y == 0)
	{
		wolf->wall_height = get_wall_height(wolf, angle, distances[0]);
		draw_wall(wolf, dots[0], ((int)dots[0].x) % 64, 0);
	}
	else if (distances[0] > distances[1])
	{
		wolf->wall_height = get_wall_height(wolf, angle, distances[1]);
		draw_wall(wolf, dots[1], ((int)dots[1].y) % 64, 1);
	}
	else
	{
		wolf->wall_height = get_wall_height(wolf, angle, distances[0]);
		draw_wall(wolf, dots[0], ((int)dots[0].x) % 64, 0);
	}
}
