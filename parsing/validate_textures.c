#include "../cub3d.h"

int	include_xpm(char *str)
{
	char	*ext;
	char	*res;

	ext = ft_strchr(str, '.');
	res = ft_strnstr(ext, ".xpm", 4);
	if (ext == NULL || res == NULL)
		return (1);
	return (0);
}

int	check_textures(t_data *prog)
{
	if (prog->maze.no == NULL || prog->maze.so == NULL || prog->maze.we == NULL
		|| prog->maze.ea == NULL || prog->maze.f < 0 || prog->maze.c < 0)
		return (1);
	if (include_xpm(prog->maze.no) || include_xpm(prog->maze.so)
		|| include_xpm(prog->maze.we) || include_xpm(prog->maze.ea))
		return (1);
	return (0);
}
