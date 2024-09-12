/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:42:03 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/29 13:42:04 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_skip(char *line, int flag)
{
	if (line == NULL)
		return (2);
	if (should_skip(line))
	{
		if (flag == 2)
			return (2);
		if (flag == 1)
			return (1);
	}
	return (0);
}

int	include_xpm(char *str)
{
	char	*ext;
	char	*res;

	ext = ft_strrchr(str, '.');
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
