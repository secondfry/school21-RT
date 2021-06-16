#include "parser.h"

static void	check_size(char *line, t_byte gnl_res)
{
	static size_t	width;
	size_t			len;

	len = ft_strlen(line);
	if (gnl_res == 0)
	{
		if (width == 0)
			error_exit(ERR_MAP_EMPTY);
		else
			return ;
	}
	if (!len)
		error_exit(ERR_MAP_HAS_EMPTY_LINE);
	if (width == 0)
	{
		width = len;
		return ;
	}
	if (width != len)
		error_exit(ERR_MAP_HAS_DIFFERENT_WIDTH_LINES);
}

static void	reader_dimensions(int fd, size_t *width, size_t *height)
{
	char	*line;
	char	*tmp;
	char	gnl_res;

	gnl_res = get_next_line(fd, &line);
	if (gnl_res < 1)
		error_exit(ERR_MAP_INVALID_WIDTH);
	*width = ft_atoi(line);
	tmp = ft_itoa(*width);
	if (ft_strcmp(line, tmp))
		error_exit(ERR_MAP_INVALID_WIDTH);
	ft_memdel((void **)&line);
	ft_memdel((void **)&tmp);
	gnl_res = get_next_line(fd, &line);
	if (gnl_res < 1)
		error_exit(ERR_MAP_INVALID_HEIGHT);
	*height = ft_atoi(line);
	tmp = ft_itoa(*height);
	if (ft_strcmp(line, tmp))
		error_exit(ERR_MAP_INVALID_HEIGHT);
	ft_memdel((void **)&line);
	ft_memdel((void **)&tmp);
}

static char	*reader(int fd, size_t *width, size_t *height)
{
	char	*line;
	char	*str;
	char	*tmp;
	t_byte	gnl_res;

	reader_dimensions(fd, width, height);
	str = (void *)0;
	while (1)
	{
		gnl_res = get_next_line(fd, &line);
		check_size(line, gnl_res);
		if (gnl_res < 0)
			error_exit(ERR_READ);
		tmp = ft_strnew(ft_strlen(str) + ft_strlen(line));
		if (!tmp)
			error_exit(ERR_MEM);
		ft_strcat(tmp, str);
		ft_memdel((void **)&str);
		ft_strcat(tmp, line);
		ft_memdel((void **)&line);
		str = tmp;
		if (gnl_res == 0)
			break ;
	}
	return (str);
}

static void	valid(char *map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1')
		{
			ft_memdel((void **)&map);
			error_exit(ERR_MAP_INVALID_CHARACTERS);
		}
		i++;
	}
}

void	parser(t_wolf *wolf, int fd)
{
	char	*map;
	size_t	width;
	size_t	height;

	map = reader(fd, &width, &height);
	valid(map);
	if (map[width + 1] == '1')
		error_exit(ERR_MAP_BLOCKED_PLAYER);
	if (width < 3 || height < 3)
		error_exit(ERR_MAP_SMOL);
	wolf->map_width = width;
	wolf->map_height = height;
	wolf->map = map;
	ft_putendl(map);
}
