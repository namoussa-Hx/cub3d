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

int	main(int ac, char **av)
{
	t_data	data;

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
