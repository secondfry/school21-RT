#include "error.h"

void	error_exit(int c)
{
	if (c == ERR_OPEN)
		ft_putendl_fd("Can't open.", 2);
	if (c == ERR_READ)
		ft_putendl_fd("Can't read.", 2);
	if (c == ERR_MEM)
		ft_putendl("Memory error.");
	if (c == ERR_MAP_INVALID_CHARACTERS)
		ft_putendl_fd("Map has invalid characters.", 2);
	if (c == ERR_MAP_EMPTY)
		ft_putendl_fd("Map is empty.", 2);
	if (c == ERR_MAP_HAS_EMPTY_LINE)
		ft_putendl_fd("Map has empty line in it.", 2);
	if (c == ERR_MAP_HAS_DIFFERENT_WIDTH_LINES)
		ft_putendl_fd("Map has different width lines in it.", 2);
	if (c == ERR_MAP_INVALID_WIDTH)
		ft_putendl_fd("Map has invalid width.", 2);
	if (c == ERR_MAP_INVALID_HEIGHT)
		ft_putendl_fd("Map has invalid height.", 2);
	if (c == ERR_MAP_BLOCKED_PLAYER)
		ft_putendl_fd("Player position is blocked on the map.", 2);
	if (c == ERR_MAP_SMOL)
		ft_putendl_fd("Map is less than 3x3.", 2);
	if (c == ERR_INVALID_DEFINE)
		ft_putendl_fd("Invalid defines.", 2);
	exit(c);
}
