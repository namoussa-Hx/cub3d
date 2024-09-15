/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:42:12 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/29 13:42:13 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_empty(t_map *maze)
{
	int	i;
	int	h;

	h = 1;
	while (h < maze->height)
	{
		i = 0;
		while (maze->map[h][i] != '\n' && maze->map[h][i] != '\0')
		{
			if (check_valid_char(maze->map[h][i], 2))
			{
				if (check_valid_char(maze->map[h][i + 1], 1)
					|| check_valid_char(maze->map[h][i - 1], 1)
					|| check_valid_char(maze->map[h + 1][i], 1)
					|| check_valid_char(maze->map[h - 1][i], 1))
					return (1);
			}
			i++;
		}
		h++;
	}
	return (0);
}

int	last_line(t_map *maze, int h)
{
	int		j;
	char	*line;

	j = 0;
	line = ft_strtrim(maze->map[h], " ");
	if (!line)
		return (1);
	while (line[j])
	{
		if ((line[j] >= 9 && line[j] <= 13) || line[j] == 32)
		{
			j++;
			continue ;
		}
		if (line[j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_first_last_line(t_map *maze)
{
	int		h;
	int		j;
	char	*line;

	j = 0;
	line = ft_strtrim(maze->map[0], " ");
	if (!line)
		return (1);
	while (line[j])
	{
		if ((line[j] >= 9 && line[j] <= 13) || line[j] == 32)
		{
			j++;
			continue ;
		}
		if (line[j] != '1')
			return (1);
		j++;
	}
	h = maze->height - 1;
	if (last_line(maze, h))
		return (1);
	return (0);
}

int	check_end_line(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while ((line[len] >= 9 && line[len] <= 13) || line[len] == ' '
		|| line[len] == '\n')
		len--;
	if (line[len] != '1')
		return (1);
	return (0);
}

int	validate_walls(t_map *maze)
{
	int	h;
	int	i;

	if (!maze->map[0] || !maze->map[maze->height - 1])
		return (1);
	if (check_first_last_line(maze))
		return (1);
	h = 1;
	i = 0;
	while (h < maze->height - 1)
	{
		if ((maze->map[h][i] >= 9 && maze->map[h][i] <= 13)
			|| maze->map[h][i] == ' ')
		{
			i++;
			continue ;
		}
		if (maze->map[h][i] != '1')
			return (1);
		else if (check_end_line(maze->map[h]))
			return (1);
		i = 0;
		h += 1;
	}
	return (0);
}
