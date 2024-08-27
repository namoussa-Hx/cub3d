#include "cub3d.h"

int check_valid_char(char c)
{
    if (c == 0 || c == 10 || (c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int check_empty(t_map *maze)
{
    int i;
    int h;

    h = 0;
    while (h < maze->height)
    {
        i = 0;
        while (maze->map[h][i] != '\n' && maze->map[h][i] != '\0')
        {
            if (maze->map[h][i] == '0')
            {
                if (i == 0 || h == 0 || maze->map[h][i + 1] == '\0' || maze->map[h][i + 1] == '\n' 
                || maze->map[h][i - 1] == '\0' || maze->map[h - 1][i] == '\0' 
                || maze->map[h + 1][i] == '\0' || maze->map[h][i - 1] == '\n')
                    return (1);
                if (check_valid_char(maze->map[h][i + 1]) || 
                    check_valid_char(maze->map[h][i - 1]) || 
                    check_valid_char(maze->map[h + 1][i]) || 
                    check_valid_char(maze->map[h - 1][i]))
                    return (1);
            }
            i++;
        }
        h++;
    }
    return (0);
}



int check_first_last_line(t_map *maze)
{
    int h;
    int j;

    j = 0;
    while (maze->map[0][j])
    {
        if((maze->map[0][j] >= 9 && maze->map[0][j] <= 13) || maze->map[0][j] == ' ')
        {
                j++;
                continue;
        }
        if (maze->map[0][j] != '1')
            return (1);
        j++;
    }
    h = maze->height - 1;
    j = 0;
    while (maze->map[h][j])
    {
        if((maze->map[h][j] >= 9 && maze->map[h][j] <= 13) || maze->map[h][j] == ' ')
        {
                j++;
                continue;
        }
        if (maze->map[h][j] != '1')
            return (1);
        j++;
    }
    return (0);
}
int check_end_line(char *line)
{
    int len;

    len = ft_strlen(line) - 1;
    while((line[len] >= 9 && line[len] <= 13) || line[len] == ' ' || line[len] == '\n')
            len--;
    if (line[len] != '1')
            return (1);
    return (0);
}
int validate_walls(t_map *maze)
{
    int h;
    int i;

     if(!maze->map[0] || !maze->map[maze->height - 1])
        return (1);
    if(check_first_last_line(maze))
        return (1);
    h = 1;
    i = 0;
	while (h < maze->height - 1)
    {
        if ((maze->map[h][i] >= 9 && maze->map[h][i] <= 13) || maze->map[h][i] == ' ')
        {
                i++;
                continue;
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
