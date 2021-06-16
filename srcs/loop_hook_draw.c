#include "loop_hook.h"

static void	draw_wall(t_rtv *rtv, int texpos)
{
	short		start;
	short		end;
	short		row;
	t_ushort	pixel;

	start = (HEIGHT - rtv->wall_height) / 2;
	end = (HEIGHT + rtv->wall_height) / 2;
	row = start;
	if (row < 0)
		row = 0;
	while (row < end && row < HEIGHT)
	{
		pixel = (end - row - 1) * 64 / rtv->wall_height * 64 + texpos;
		rtv->mlx->img_data[row * rtv->mlx->size_line_int + rtv->column] = \
			rtv->texture \
				[TEX_ERROR] \
				[pixel];
		row++;
	}
}

void	draw(t_rtv *rtv, float angle, t_point dots[2], float distances[2])
{
	(void)angle;
	if (dots[0].x == 0 && dots[0].y == 0)
	{
		rtv->wall_height = 0;
		draw_wall(rtv, ((int)dots[1].y) % 64);
	}
	else if (dots[1].x == 0 && dots[1].y == 0)
	{
		rtv->wall_height = 0;
		draw_wall(rtv, ((int)dots[0].x) % 64);
	}
	else if (distances[0] > distances[1])
	{
		rtv->wall_height = 0;
		draw_wall(rtv, ((int)dots[1].y) % 64);
	}
	else
	{
		rtv->wall_height = 0;
		draw_wall(rtv, ((int)dots[0].x) % 64);
	}
}
