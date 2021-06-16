#include "texture.h"

static int	*texture_read(int fd, size_t size)
{
	t_byte	*data;
	int		*ret;
	size_t	len;
	size_t	i;

	if (size != 3 * 64 * 64)
		exit(0);
	data = (t_byte *)ft_memalloc(sizeof(t_byte) * size);
	if (!data)
		exit(0);
	ret = (int *)ft_memalloc(sizeof(int) * size / 3);
	if (!ret)
		exit(0);
	len = read(fd, data, size);
	if (len != size)
		exit(0);
	close(fd);
	i = 0;
	while (i < size)
	{
		ret[i / 3] = data[i] + (data[i + 1] << 8) + (data[i + 2] << 16);
		i += 3;
	}
	ft_memdel((void **)&data);
	return (ret);
}

static int	*texture_load(char *filename)
{
	int		fd;
	size_t	len;
	t_byte	header[54];
	int		dimensions[2];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_OPEN);
	len = read(fd, header, 0);
	if (len < 0)
		error_exit(ERR_READ);
	len = read(fd, header, 54);
	if (len != 54)
		exit(0);
	dimensions[0] = *(int *)&header[18];
	dimensions[1] = *(int *)&header[22];
	return (texture_read(fd, 3 * dimensions[0] * dimensions[1]));
}

void	init_textures(t_wolf *wolf)
{
	wolf->texture[TEX_ISAAC_NORTH] = texture_load(TEX_ISAAC_NORTH_FILENAME);
	wolf->texture[TEX_ISAAC_EAST] = texture_load(TEX_ISAAC_EAST_FILENAME);
	wolf->texture[TEX_ISAAC_SOUTH] = texture_load(TEX_ISAAC_SOUTH_FILENAME);
	wolf->texture[TEX_ISAAC_WEST] = texture_load(TEX_ISAAC_WEST_FILENAME);
	wolf->texture[TEX_ERROR] = texture_load(TEX_ERROR_FILENAME);
	wolf->texture[TEX_ART_NORTH] = texture_load(TEX_ART_NORTH_FILENAME);
	wolf->texture[TEX_ART_EAST] = texture_load(TEX_ART_EAST_FILENAME);
	wolf->texture[TEX_ART_SOUTH] = texture_load(TEX_ART_SOUTH_FILENAME);
	wolf->texture[TEX_ART_WEST] = texture_load(TEX_ART_WEST_FILENAME);
}
