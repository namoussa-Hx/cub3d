/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:41:42 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/29 13:41:44 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*parse_texture(char *line, int *counter)
{
	int		i;
	int		j;
	char	*texture;
	char	*str;

	i = 0;
	*counter += 1;
	str = ft_strtrim(line, " ");
	if (str == NULL)
		return (NULL);
	i += 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j] && line[j] != '\n' && line[j] != ' ')
		j++;
	texture = ft_substr(line, i, j - i);
	return (texture);
}

int	check_color(char *str, int *color)
{
	int		i;
	int		r;
	int		g;
	int		b;
	char	**res;

	i = 0;
	i++;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	res = ft_split(str + i, ',');
	if (res == NULL)
		return (-1);
	if (ft_isdigit(res[0]) == 0 || ft_isdigit(res[1]) == 0
		|| ft_isdigit(res[2]) == 0)
		return (-1);
	r = ft_atoi(res[0]);
	g = ft_atoi(res[1]);
	b = ft_atoi(res[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (-1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

int	parse_color(char *line, int *counter)
{
	int		color;
	char	*str;

	*counter += 1;
	str = ft_strtrim(line, " ");
	if (str == NULL)
		return (-1);
	if (check_color(str, &color))
		return (-1);
	return (color);
}

int	check_map_line(char *line, t_data *prog)
{
	int	counter;

	counter = 0;
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		prog->maze.no = parse_texture(line, &counter);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		prog->maze.so = parse_texture(line, &counter);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		prog->maze.we = parse_texture(line, &counter);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		prog->maze.ea = parse_texture(line, &counter);
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		prog->maze.f = parse_color(line, &counter);
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		prog->maze.c = parse_color(line, &counter);
	return (counter);
}

int	parse_cub(char *file, t_data *prog)
{
	int		fd;
	int		i;
	char	*line;
	int		counter;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		i = 0;
		counter += check_map_line(line, prog);
		free(line);
		continue ;
	}
	if (counter != 6 || check_is_map_valid(prog, file) || check_textures(prog)
		|| check_extension(file))
		return (1);
	close(fd);
	return (0);
}
