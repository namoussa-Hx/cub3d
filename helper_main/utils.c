/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:58:51 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:39:27 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_half(t_data *data)
{
	data->x_mouse_prev = 0;
	data->hide_mouse = 0;
	data->is_door = 0;
	data->image_door = NULL;
	data->addr_door = NULL;
	data->scale_door = NULL;
	data->width_door = 0;
	data->height_door = 0;
	data->bpp_door = 0;
	data->size_line_door = 0;
	data->distance_to_door = 0;
	data->is_door_open = 0;
	data->endian_door = 0;
	data->x_door = -1;
	data->y_door = -1;
	data->real_dist = 0;
}

void	init_data(t_data *data)
{
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
	init_half(data);
}

int	mouse_hook(int x_mouse, int y_mouse, t_data *game)
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
	if (game->hide_mouse == 0)
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	mouse_hide(t_data *game)
{
	game->hide_mouse = 0;
	mlx_mouse_hide(game->mlx, game->win);
	return (0);
}

int	destroy_all(t_data *game)
{
	int	i;

	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img);
	while (i < 6)
	{
		mlx_destroy_image(game->mlx, game->walls->images[i]);
		i++;
	}
	i = 0;
	while (i < 37)
	{
		mlx_destroy_image(game->mlx, game->walls->player[i]);
		i++;
	}
	free_all();
	exit(0);
	return (0);
}
