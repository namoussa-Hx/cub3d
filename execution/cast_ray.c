/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:07:01 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/14 16:33:30 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_side(t_data *game)
{
	if (game->vector.side_dist_x < game->vector.side_dist_y)
	{
		game->vector.side_dist_x += game->vector.delta_dist_x;
		game->vector.map_x += game->vector.step_x;
		game->vector.side = 0;
	}
	else
	{
		game->vector.side_dist_y += game->vector.delta_dist_y;
		game->vector.map_y += game->vector.step_y;
		game->vector.side = 1;
	}
	if (game->vector.map_y < 0 || game->vector.map_y >= game->maze.height
		|| game->vector.map_x < 0 || game->vector.map_x >= game->maze.width)
		return ;
	if (game->maze.map[game->vector.map_y][game->vector.map_x] == '1'
		|| game->maze.map[game->vector.map_y][game->vector.map_x] == 'D')
	{
		game->vector.hit = 1;
		if (game->maze.map[game->vector.map_y][game->vector.map_x] == 'D')
			game->is_door = 1;
	}
}

void	ray_dir(t_data *game, int tile_size)
{
	raydirx(game, tile_size);
	if (game->vector.ray_dir_y < 0)
	{
		game->vector.step_y = -1;
		game->vector.side_dist_y = (game->player.player_y / tile_size
				- game->vector.map_y) * game->vector.delta_dist_y;
	}
	else
	{
		game->vector.step_y = 1;
		game->vector.side_dist_y = (game->vector.map_y + 1.0
				- game->player.player_y / tile_size)
			* game->vector.delta_dist_y;
	}
}

void	ray_init(t_data *game, float angle, int tile_size)
{
	game->vector.map_x = (int)(game->player.player_x / tile_size);
	game->vector.map_y = (int)(game->player.player_y / tile_size);
	game->vector.ray_dir_x = cosf(angle);
	game->vector.ray_dir_y = sinf(angle);
	game->vector.delta_dist_x = fabs(1 / game->vector.ray_dir_x);
	game->vector.delta_dist_y = fabs(1 / game->vector.ray_dir_y);
	game->vector.hit = 0;
}

void	wall_dist_door(t_data *game, int tile_size)
{
	if (game->vector.side == 0)
	{
		game->vector.perp_wall_dist = (game->vector.map_x
				- game->player.player_x / tile_size + (1 - game->vector.step_x)
				/ 2) / game->vector.ray_dir_x;
	}
	else
	{
		game->vector.perp_wall_dist = (game->vector.map_y
				- game->player.player_y / tile_size + (1 - game->vector.step_y)
				/ 2) / game->vector.ray_dir_y;
	}
	if (game->maze.map[game->vector.map_y][game->vector.map_x] == 'D')
	{
		if (game->maze.map[game->vector.map_y][game->vector.map_x] == 'D')
			if (game->vector.perp_wall_dist < 2.5)
				game->is_door_open = 2;
	}
}

void	cast_ray_dda(t_data *game, float angle, int ray_index, int tile_size)
{
	ray_init(game, angle, tile_size);
	ray_dir(game, tile_size);
	while (game->vector.hit == 0)
		check_side(game);
	wall_dist_door(game, tile_size);
	render_3d_projection(game, game->vector.perp_wall_dist * tile_size,
		ray_index);
}
