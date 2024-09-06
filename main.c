/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:45:39 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/04 23:35:06 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->maze.map = NULL;
	data->maze.no = NULL;
	data->maze.so = NULL;
	data->maze.we = NULL;
	data->maze.ea = NULL;
	data->maze.f = 0;
	data->maze.c = 0;
	data->maze.height = 0;
	data->player.angle = 0;
	data->player.fov = PI / 3;
	data->player.player_x = 0;
    data->player.player_y = 0;
    data->player.x = 0;
    data->player.y = 0;
    data->player_face = 0;
    data->x_mouse_prev = 0;
}

int is_wall(t_data *game, int x, int y, int tile_size)
{
    int map_x;
    int map_y;
    map_x = x / tile_size;
    map_y = y / tile_size;
    if (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT)
        return 1;

    return (game->maze.map[map_y][map_x] == '1');
}

void init_player(t_data *game, int tile_size) 
{
    float start_x;
    float start_y;
    start_x = WIDTH / 2.0;
    start_y = HEIGHT / 2.0;

    while (is_wall(game, start_x, start_y, tile_size)) 
    {
        start_x += tile_size; 
        if (start_x >= WIDTH) 
        {
            start_x = tile_size;
            start_y += tile_size; 
            if (start_y >= HEIGHT)
             {
                start_x = tile_size;
                start_y = tile_size;
            }
        }
    }
    game->player.player_x = start_x;
    game->player.player_y = start_y;
}

double getTicks()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0); 
}

// void player_facing(t_data *data)
// {

    


// }
// int update(t_data *game)
// {
//     int x = 0;
//     int tile_size = 30;
//     float ray_angle;

   
//     memset(game->img_data, 0, WIDTH * HEIGHT * (game->bpp / 8));


//     render_color(game);
//     render_flor(game);

//     while (x < WIDTH)
//     {
//         ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0 / tanf(game->player.fov / 2.0)));
//         cast_ray_dda(game, ray_angle, x, tile_size);
//         x++;
//     }

    
//     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

//     return 0;
// }

int update(t_data *game)
{
    int x = 0;
    int tile_size = 30;
    float ray_angle;

    memset(game->img_data, 0, WIDTH * HEIGHT * (game->bpp / 8));

    render_color(game);
    render_flor(game);
    while (x < WIDTH)
    {
        ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0 / tanf(game->player.fov / 2.0)));
        cast_ray_dda(game, ray_angle, x, tile_size);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

int mouse_hook(int x_mouse, int y_mouse, t_data *game)
{
    (void)y_mouse;
      if (game->player.angle >= 2 * PI)
            game->player.angle -= 2 * PI;
     if (game->player.angle < 0)
            game->player.angle += 2 * PI;
    printf("angle %f\n", game->player.angle);
    printf("x_mouse %d\n", x_mouse);
    printf("x_mouse_prev %d\n", game->x_mouse_prev);
    if (x_mouse > game->x_mouse_prev)
        game->player.angle += 0.05;
    else if (x_mouse < game->x_mouse_prev)
        game->player.angle -= 0.05;
    game->x_mouse_prev = x_mouse;
    return 0;
}

int	main(int ac, char **av)
{
	t_data	data;
	int tile_size;

	if (ac == 2)
	{
		init_data(&data);
		if (parse_cub(av[1], &data) && print_error("Error \n"))
			        return (1);
        data.textures = malloc(sizeof(t_images));
        ft_bzero(data.textures, sizeof(t_images));
        data.maze.width=  ft_strlen(data.maze.map[0]);
        tile_size = 30;
        data.player.player_x = (data.player.x * tile_size) + (tile_size / 2);
        data.player.player_y = (data.player.y * tile_size) + (tile_size / 2);
        data.x_mouse_prev = WIDTH / 2; 
        init_textures(&data);
        data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
        data.img_data = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
        update(&data);
    mlx_hook(data.win, 02, 1L << 0, key_hook, &data);
    mlx_hook(data.win, 6, 1L<<6, mouse_hook, &data);
    mlx_loop_hook(data.mlx, update, &data);
    mlx_loop(data.mlx);
    mlx_destroy_image(data.mlx, data.img);
      free(data.maze.map);
	}
	else
		print_error("Error: invalid number of arguments\n");
	return (0);
}
