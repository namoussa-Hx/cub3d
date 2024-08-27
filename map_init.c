#include "cub3d.h"

int should_skip(char *line)
{
    int i = 0;

    while (line[i] == ' ')
        i++;
    if (line[i] == '\0' || line[i] == '\n')
        return (1);
    if(ft_strnstr(line, "NO", ft_strlen(line)) 
    || ft_strnstr(line, "SO", ft_strlen(line)) 
    || ft_strnstr(line, "WE", ft_strlen(line))
    || ft_strnstr(line, "EA", ft_strlen(line))
    || ft_strnstr(line, "F", ft_strlen(line))
    || ft_strnstr(line, "C", ft_strlen(line)))
        return (1);
    return (0);
}

int calcule_map_size(int fd, t_map *prog)
{
    char *line;
    int len = 0;

 
    while ((line = get_next_line(fd)))
    {
        
        if (should_skip(line))
        {
            free(line);
            continue;
        }
        len++;
        free(line);
    }
    prog->height = len;
    close(fd);
    return (len);
}


int map_copy(t_map *prog, char *file)
{
    char *line;
    int j = 0;
    int len = 0;
    int fd1 = 0;
    int fd = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (1); 

    len  = calcule_map_size(fd, prog);
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
            continue;
        }
        prog->map[j] = ft_strdup(line);
        j++;
        free(line);
    }
    prog->map[j] = NULL;
    close(fd1);
    return (0);
}
