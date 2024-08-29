/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:41:33 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/29 13:41:35 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	map_size(t_map *prog, int *lenght, char *file)
{
	char	*line;
	int		len;
	int		fd;
	int		flag;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	len = 0;
	flag = 1;
	*lenght = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (is_skip(line, flag) == 1)
			continue ;
		else if (is_skip(line, flag) == 2)
			break ;
		flag = 2;
		len++;
		if (*lenght < (int)ft_strlen(line))
			*lenght = ft_strlen(line);
		free(line);
	}
	return (prog->height = len, close(fd), len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

char	*my_strdup(const char *s1, int lenght)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)ft_calloc(lenght + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	map_copy(t_map *prog, char *file)
{
	char	*line;
	int		j;
	int		fd1;
	int		lenght;
	int		flag;

	j = 0;
	flag = 1;
	prog->map = (char **)malloc(sizeof(char *) * (map_size(prog, &lenght, file)
				+ 1));
	fd1 = open(file, O_RDONLY);
	if (fd1 == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd1);
		if (is_skip(line, flag) == 1)
			continue ;
		else if (is_skip(line, flag) == 2)
			break ;
		flag = 2;
		prog->map[j++] = my_strdup(line, lenght);
		free(line);
	}
	return (prog->map[j] = NULL, close(fd1), 0);
}
