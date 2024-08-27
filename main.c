#include "cub3d.h"

int print_error(char *str)
{
    write(2, str, ft_strlen(str));
    return (1);
}

int check_extension(char *file)
{
    char *ext = ft_strrchr(file, '.');
    if (ext == NULL || ft_strncmp(ext, ".cub", 5) != 0)
        return (1);
    return (0);
}

char *parse_texture(char *line)
{
    int i = 0;
    int j;
    char *texture;

    while (line[i] == ' ')
        i++;
    i += 2;
    while (line[i] == ' ')
        i++;
    j = i;
    while (line[j] && line[j] != ' ')
        j++;
    texture = ft_substr(line, i, j - i);
    return (texture);
}

int parse_color(char *line)
{
    int i = 0;
    int r, g, b;
    char **res;
    int color;

    while (line[i] == ' ')
        i++;
    if (line[i] == 'F' || line[i] == 'C')
    {
        i++;
        while (line[i] == ' ')
            i++;
        res = ft_split(line + i, ',');
        if (ft_isdigit(res[0]) != 0 || ft_isdigit(res[1]) != 0 || ft_isdigit(res[2]) != 0)
        {
			   r = ft_atoi(res[0]);
               g = ft_atoi(res[1]);
               b = ft_atoi(res[2]);
			if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                     return (-1);
        }
        else
            return (-1);
        color = (r << 16) | (g << 8) | b;
        free(res[0]);
        free(res[1]);
        free(res[2]);
        free(res);
        return (color);
    }
    return (-1);
}



int my_strchr(char *str, char *c)
{
    int i = 0;
    while (str[i])
    {
        if (ft_strchr(c, str[i]))
            return (1);
        i++;
    }
    return (0);
}

int parse_cub(char *file, t_data *prog)
{
    int fd;
    int i;
    char *line;
    if (check_extension(file))
        return (1);

    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)))
    {
        i = 0;
        if (ft_strnstr(line, "NO", ft_strlen(line)))
            prog->maze.no = parse_texture(line);
        else if (ft_strnstr(line, "SO", ft_strlen(line)))
            prog->maze.so = parse_texture(line);
        else if (ft_strnstr(line, "WE", ft_strlen(line)))
            prog->maze.we = parse_texture(line);
        else if (ft_strnstr(line, "EA", ft_strlen(line)))
            prog->maze.ea = parse_texture(line);
        else if (ft_strnstr(line, "F", ft_strlen(line)))
            prog->maze.f = parse_color(line);
        else if (ft_strnstr(line, "C", ft_strlen(line)))
            prog->maze.c = parse_color(line);
        else if (line[i] == '\0' || line[i] == '\n')
        {
            free(line);
            continue;
        }
        else
         break ;
        free(line);
    }
    if (check_is_map_valid(prog, file))
        return (1);
    if(prog->maze.no == NULL || prog->maze.so == NULL || prog->maze.we == NULL
        || prog->maze.ea == NULL || (prog->maze.f < 0 && prog->maze.c < 0))
        return (1);
    close(fd);
    return (0);
}

void init_data(t_data *data)
{
    // data->mlx = mlx_init();
    // data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
    data->maze.map = NULL;
    data->maze.no = NULL;
    data->maze.so = NULL;
    data->maze.we = NULL;
    data->maze.ea = NULL;
    data->maze.f = 0;
    data->maze.c = 0;
    data->maze.height = 0;
    data->player.x = 0;
    data->player.y = 0;
    data->player.dir_x = 0;
    data->player.dir_y = 0;
    data->player.player_x = 0;
    data->player.player_y = 0;
    data->player.move_speed = 0;
    data->player.rot_speed = 0;

}

int main(int ac, char **av)
{
    t_data data;

    if (ac == 2)
    {
        init_data(&data);
        if (parse_cub(av[1], &data))
        {
            print_error("Error \n");
            return (1);
        }
     
    }
    else
        print_error("Error: invalid number of arguments\n");
    

    return (0);
}

