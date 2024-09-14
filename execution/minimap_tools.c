/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:50:51 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/14 19:19:09 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_tiles(t_minimap *mini, t_data *game)
{
	mini->center_x = WIDTH - MINIMAP_RADIUS - 10;
	mini->center_y = MINIMAP_RADIUS;
	mini->player_x = game->player.player_x / 30.0f;
	mini->player_y = game->player.player_y / 30.0f;
	mini->y = -MINIMAP_RADIUS;
}

void	check_position(t_data *game, t_minimap *mini)
{
	mini->map_x = (int)(mini->player_x + mini->x / (float)TILE_SIZE);
	mini->map_y = (int)(mini->player_y + mini->y / (float)TILE_SIZE);
	mini->color = 0;
	if (mini->map_x >= 0 && mini->map_x < game->maze.width && mini->map_y >= 0
		&& mini->map_y < game->maze.height)
	{
		if (game->maze.map[mini->map_y][mini->map_x] == '1')
			mini->color = 0x000000;
		else if (game->maze.map[mini->map_y][mini->map_x] == 'D')
			mini->color = 0x8B4513;
		else if (game->maze.map[mini->map_y][mini->map_x] == '0')
			mini->color = 0xADD8E6;
		else if (game->maze.map[mini->map_y][mini->map_x] == 'W'
			|| game->maze.map[mini->map_y][mini->map_x] == 'E'
			|| game->maze.map[mini->map_y][mini->map_x] == 'S'
			|| game->maze.map[mini->map_y][mini->map_x] == 'N')
			mini->color = 0xADD8E6;
	}
}

int	check_circle_and_init(t_data *game, t_minimap *mini)
{
	if (is_inside_circle(mini->x + MINIMAP_RADIUS, mini->y + MINIMAP_RADIUS,
			MINIMAP_RADIUS - 2))
	{
		check_position(game, mini);
		return (1);
	}
	return (0);
}

void	draw_map_tiles(t_data *game)
{
	t_minimap	*mini;

	mini = ft_malloc(sizeof(t_minimap));
	init_player_tiles(mini, game);
	while (mini->y < MINIMAP_RADIUS)
	{
		mini->x = -MINIMAP_RADIUS;
		while (mini->x < MINIMAP_RADIUS)
		{
			if (check_circle_and_init(game, mini))
			{
				mini->screen_x = mini->center_x + mini->x;
				mini->screen_y = mini->center_y + mini->y;
				mini->pixel_index = (mini->screen_y * game->size_line)
					+ (mini->screen_x * (game->bpp / 8));
				*((unsigned int *)(game->img_data
							+ mini->pixel_index)) = mini->color;
			}
			mini->x++;
		}
		mini->y++;
	}
}

void	draw_player_marker_init(t_minimap *mini)
{
	mini->center_x = WIDTH - MINIMAP_RADIUS - 10;
	mini->center_y = MINIMAP_RADIUS;
	mini->y = -PLAYER_MARKER_SIZE;
}
