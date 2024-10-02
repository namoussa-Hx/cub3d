/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:41:33 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:15:08 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	}
	prog->width = *lenght;
	return (prog->height = len, close(fd), len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_malloc(count * size);
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

int	is_expect(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, " ");
	if (temp == NULL || temp[0] == '\0')
		return (0);
	return (1);
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
	prog->map = (char **)ft_malloc(sizeof(char *) * (map_size(prog, &lenght,
					file) + 1));
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
	}
	return (prog->map[j] = NULL, _r(fd1));
}
