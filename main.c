/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:45:39 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/08 17:54:51 by elchakir         ###   ########.fr       */
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
    data->x_mouse_prev = 0;
    data->hide_mouse = 0;
    data->enemy.x = 0;
    data->enemy.y = 0;
}

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
    render_minimap(game);
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
    if (x_mouse > game->x_mouse_prev)
        game->player.angle += 0.05;
    else if (x_mouse < game->x_mouse_prev)
        game->player.angle -= 0.05;
    if(game->hide_mouse == 0)
        mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
    return 0;
}
int mouse_hide(t_data *game)
{
    game->hide_mouse = 0;
    mlx_mouse_hide(game->mlx, game->win);
    return 0;
}


int ft_exit(t_data *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
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
        data.walls = malloc(sizeof(t_images));
        ft_bzero(data.walls, sizeof(t_images));

        data.textures = malloc(sizeof(t_textures));
        ft_bzero(data.textures, sizeof(t_textures));

        tile_size = 30;
        data.player.player_x = (data.player.x * tile_size) + (tile_size / 2);
        data.player.player_y = (data.player.y * tile_size) + (tile_size / 2);
        data.x_mouse_prev = WIDTH / 2; 
        init_walls(&data);
        data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
        data.img_data = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
        update(&data);
    mlx_hook(data.win, 02, 1L << 0, key_hook, &data);
    mlx_hook(data.win, 6, 1L<<6, mouse_hook, &data);
    mlx_hook(data.win, 7, 1L << 4, mouse_hide, &data);
    mlx_hook(data.win, 17, 0, ft_exit, &data);
    mlx_mouse_hide(data.mlx, data.win);
    mlx_loop_hook(data.mlx, update, &data);
    mlx_loop(data.mlx);
    mlx_destroy_image(data.mlx, data.img);
    mlx_mouse_show(data.mlx, data.win);
      free(data.maze.map);
	}
	else
		print_error("Error: invalid number of arguments\n");
	return (0);
}
