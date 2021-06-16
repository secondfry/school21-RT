#include "error.h"

void	error_exit(int c)
{
	if (c == ERR_OPEN)
		ft_putendl_fd("Can't open.", 2);
	if (c == ERR_READ)
		ft_putendl_fd("Can't read.", 2);
	if (c == ERR_MEM)
		ft_putendl("Memory error.");
	if (c == ERR_INVALID_DEFINE)
		ft_putendl_fd("Invalid defines.", 2);
	exit(c);
}
