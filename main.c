/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:45:39 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/29 13:45:41 by namoussa         ###   ########.fr       */
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
}

int	main(int ac, char **av)
{
	t_data	data;
	// int x;
	int tile_size;

		// x = 0;
	if (ac == 2)
	{
		init_data(&data);
		if (parse_cub(av[1], &data))
		{
			print_error("Error \n");
			return (1);
		}
		tile_size = fmin(WIDTH / 2, HEIGHT / 2);
		//     while (x < WIDTH) 
		// 	{
        // float ray_angle = data.player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0 / tanf(data.player.fov / 2.0)));
        // cast_ray_dda(&data, ray_angle, x, tile_size);
        // x++;
        // }
   
    // mlx_hook(data.win, 02, 1L << 0, key_hook, &data);
	draw_map(&data, 20);
    mlx_loop(data.mlx);

    free(data.maze.map);
	}
	else
		print_error("Error: invalid number of arguments\n");
	return (0);
}
