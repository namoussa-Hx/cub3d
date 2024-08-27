#include "cub3d.h"

int	ft_check_chars(t_map *maze)
{
	int	h;
	int	w;

	h = 1;
	while (h < maze->height - 1)
    {
        w = 0;
        while (maze->map[h][w] != '\n' && maze->map[h][w] != '\0')
        {
            if(maze->map[h][w] == ' ' || (maze->map[h][w] >= 9 && maze->map[h][w] <= 13))
            {
                w++;
                continue;
            }
            if (ft_strchr("01NSEW", maze->map[h][w]) == 0)
                return (1);
            w++;
        }
        h++;
    }
	return (0);
}

int	check_conditions(char ch, int count)
{
	if ((ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W') && count > 1)
		return (1);
	return (0);
}

int	ft_check_char(t_data *data, char ch, int *count)
{
	int	h;
	int	w;

	*count = 0;
	h = 1;
    while (h < data->maze.height - 1)
    {
        w = 0;
        while (data->maze.map[h][w] != '\n' && data->maze.map[h][w] != '\0')
        {
            if(data->maze.map[h][w] == ' ' || (data->maze.map[h][w] >= 9 && data->maze.map[h][w] <= 13))
            {
                w++;
                continue;
            }
            if (data->maze.map[h][w] == 'N' || data->maze.map[h][w] == 'S' 
            || data->maze.map[h][w] == 'E' || data->maze.map[h][w] == 'W')
            {
                data->player.player_x = w;
                data->player.player_y = h;
            }
            if (data->maze.map[h][w] == ch)
                *count += 1;
            w++;
        }
        h++;
    }
	return (check_conditions(ch, *count));
}

int	check_every_char(t_data *prog)
{
	int	count_n;
    int count_s;
    int count_e;
    int count_w;

	if ((ft_check_chars(&prog->maze)))
        return (1);
	if ((ft_check_char(prog, 'N', &count_n)))
        return (1);
	if ((ft_check_char(prog, 'E', &count_s)))
        return (1);
	if ((ft_check_char(prog, 'S', &count_e)))
        return (1);
    if ((ft_check_char(prog, 'W', &count_w)))
        return (1);
    if((count_n == 0 && count_s == 0 && count_e == 0 && count_w == 0) 
            || (count_n == 1 && (count_s != 0 || count_e != 0 || count_w != 0))
            || (count_s == 1 && (count_n != 0 || count_e != 0 || count_w != 0))
            || (count_e == 1 && (count_s != 0 || count_n != 0 || count_w != 0))
            || (count_w == 1 && (count_s != 0 || count_e != 0 || count_n != 0)))
                return (1);
 return (0);
}

int check_is_map_valid(t_data *prog, char *file)
{
    int i;

    i = 0;
    map_copy(&prog->maze, file);
   if(validate_walls(&prog->maze))
        return (1);
    if(check_every_char(prog))
        return (1);
    if(check_empty(&prog->maze))
        return (1);
    return (0);
}
