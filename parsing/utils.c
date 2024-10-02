/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:27:24 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/12 14:27:29 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_player_angle(t_data *data, char c)
{
	if (c == 'N')
		data->player.angle = 3 * PI / 2;
	if (c == 'S')
		data->player.angle = PI / 2;
	if (c == 'E')
		data->player.angle = 0;
	if (c == 'W')
		data->player.angle = PI;
}

int	should_skip(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	if (ft_strnstr(line, "NO", ft_strlen(line)) || ft_strnstr(line, "SO",
			ft_strlen(line)) || ft_strnstr(line, "WE", ft_strlen(line))
		|| ft_strnstr(line, "EA", ft_strlen(line)) || ft_strnstr(line, "F",
			ft_strlen(line)) || ft_strnstr(line, "C", ft_strlen(line)))
		return (1);
	return (0);
}

int	is_comma(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

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
	while (str[i] == ' ')
		i++;
	j = i;
	while (str[j] && str[j] != '\n')
		j++;
	texture = ft_substr(str, i, j - i);
	return (texture);
}
