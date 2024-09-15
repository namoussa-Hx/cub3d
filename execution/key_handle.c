/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:28:54 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/15 15:51:39 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	right(t_data *game, int keycode, int *map_x, int *map_y)
{
	float	new_x;
	float	new_y;

	if (keycode == RIGHT)
	{
		new_x = game->player.player_x + cosf(game->player.angle + (PI / 2))
			* MOVE_SPEED;
		new_y = game->player.player_y + sinf(game->player.angle + (PI / 2))
			* MOVE_SPEED;
		*map_x = (int)((new_x + copysignf(6, cosf(game->player.angle + (PI
								/ 2)))) / 30);
		*map_y = (int)((new_y + copysignf(6, sinf(game->player.angle + (PI
								/ 2)))) / 30);
		if (game->maze.map[*map_y][(int)(game->player.player_x / 30)] != '1')
		{
			game->player.player_y = new_y;
		}
		if (game->maze.map[(int)(game->player.player_y / 30)][*map_x] != '1')
		{
			game->player.player_x = new_x;
		}
	}
}

void	up(t_data *game, int keycode, int *map_x, int *map_y)
{
	float	new_x;
	float	new_y;

	if (keycode == UP)
	{
		new_x = game->player.player_x + cosf(game->player.angle) * MOVE_SPEED;
		new_y = game->player.player_y + sinf(game->player.angle) * MOVE_SPEED;
		*map_x = (int)((new_x + copysignf(6, cosf(game->player.angle))) / 30);
		*map_y = (int)((new_y + copysignf(6, sinf(game->player.angle))) / 30);
		if (game->maze.map[*map_y][(int)(game->player.player_x / 30)] != '1')
		{
			game->player.player_y = new_y;
		}
		if (game->maze.map[(int)(game->player.player_y / 30)][*map_x] != '1')
		{
			game->player.player_x = new_x;
		}
	}
}

void	down(t_data *game, int keycode, int *map_x, int *map_y)
{
	float	new_x;
	float	new_y;

	if (keycode == DOWN)
	{
		new_x = game->player.player_x - cosf(game->player.angle) * MOVE_SPEED;
		new_y = game->player.player_y - sinf(game->player.angle) * MOVE_SPEED;
		*map_x = (int)((new_x - copysignf(6, cosf(game->player.angle))) / 30);
		*map_y = (int)((new_y - copysignf(6, sinf(game->player.angle))) / 30);
		if (game->maze.map[*map_y][(int)(game->player.player_x / 30)] != '1')
		{
			game->player.player_y = new_y;
		}
		if (game->maze.map[(int)(game->player.player_y / 30)][*map_x] != '1')
		{
			game->player.player_x = new_x;
		}
	}
}

int	key_hook(int keycode, t_data *game)
{
	int	map_x;
	int	map_y;

	if (keycode == 65361)
		game->player.angle -= ROT_SPEED;
	if (keycode == 65363)
		game->player.angle += ROT_SPEED;
	up(game, keycode, &map_x, &map_y);
	down(game, keycode, &map_x, &map_y);
	left(game, keycode, &map_x, &map_y);
	right(game, keycode, &map_x, &map_y);
	if (keycode == 32)
	{
		game->hide_mouse = 1;
		mlx_mouse_show(game->mlx, game->win);
	}
	if (keycode == 65307)
	{
		destroy_all(game);
		exit(0);
	}
	return (0);
}

void	raydirx(t_data *game, int tile_size)
{
	if (game->vector.ray_dir_x < 0)
	{
		game->vector.step_x = -1;
		game->vector.side_dist_x = (game->player.player_x / tile_size
				- game->vector.map_x) * game->vector.delta_dist_x;
	}
	else
	{
		game->vector.step_x = 1;
		game->vector.side_dist_x = (game->vector.map_x + 1.0
				- game->player.player_x / tile_size)
			* game->vector.delta_dist_x;
	}
}
