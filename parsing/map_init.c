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

int	calcule_map_size(t_map *prog, int *lenght, char *file)
{
	char	*line;
	int		len;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	len = 0;
	*lenght = 0;
	while ((line = get_next_line(fd)))
	{
		if (should_skip(line))
		{
			free(line);
			continue ;
		}
		len++;
		if (*lenght < (int)ft_strlen(line))
			*lenght = ft_strlen(line);
		free(line);
	}
	prog->height = len;
	close(fd);
	return (len);
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
	int		len;
	int		fd1;
	int		lenght;

	j = 0;
	len = calcule_map_size(prog, &lenght, file);
	prog->map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!prog->map)
		return (1);
	fd1 = open(file, O_RDONLY);
	if (fd1 == -1)
		return (1);
	while ((line = get_next_line(fd1)))
	{
		if (should_skip(line))
		{
			free(line);
			continue ;
		}
		prog->map[j++] = my_strdup(line, lenght);
		free(line);
	}
	return (prog->map[j] = NULL, close(fd1), 0);
}
