/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:06:55 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/14 19:19:21 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_init(t_minimap *mini)
{
	mini->center_x = WIDTH - MINIMAP_RADIUS - 10;
	mini->center_y = MINIMAP_RADIUS;
	mini->y = 0;
}

void	clear_minimap_area(t_data *game)
{
	t_minimap	*mini;

	mini = ft_malloc(sizeof(t_minimap));
	clear_init(mini);
	while (mini->y < MINIMAP_DIAMETER)
	{
		mini->x = 0;
		while (mini->x < MINIMAP_DIAMETER)
		{
			if (is_inside_circle(mini->x, mini->y, MINIMAP_RADIUS))
			{
				mini->screen_x = mini->center_x - MINIMAP_RADIUS + mini->x;
				mini->screen_y = mini->center_y - MINIMAP_RADIUS + mini->y;
				mini->pixel_index = (mini->screen_y * game->size_line)
					+ (mini->screen_x * (game->bpp / 8));
				*((unsigned int *)(game->img_data
							+ mini->pixel_index)) = 0x000000;
			}
			mini->x++;
		}
		mini->y++;
	}
}

void	draw_player_marker(t_data *game)
{
	t_minimap	*mini;

	mini = ft_malloc(sizeof(t_minimap));
	draw_player_marker_init(mini);
	while (mini->y <= PLAYER_MARKER_SIZE)
	{
		mini->x = -PLAYER_MARKER_SIZE;
		while (mini->x <= PLAYER_MARKER_SIZE)
		{
			if (mini->x * mini->x + mini->y * mini->y <= PLAYER_MARKER_SIZE
				* PLAYER_MARKER_SIZE)
			{
				mini->screen_x = mini->center_x + mini->x;
				mini->screen_y = mini->center_y + mini->y;
				mini->pixel_index = (mini->screen_y * game->size_line)
					+ (mini->screen_x * (game->bpp / 8));
				*((unsigned int *)(game->img_data
							+ mini->pixel_index)) = 0xFFFF00;
			}
			mini->x++;
		}
		mini->y++;
	}
}

void	draw_minimap_border(t_data *game)
{
	t_minimap	*mini;

	mini = ft_malloc(sizeof(t_minimap));
	border_init(mini);
	while (mini->y <= MINIMAP_RADIUS)
	{
		mini->x = -MINIMAP_RADIUS;
		while (mini->x <= MINIMAP_RADIUS)
		{
			check_border(mini, game);
			mini->x++;
		}
		mini->y++;
	}
}

int	render_minimap(t_data *game)
{
	clear_minimap_area(game);
	draw_map_tiles(game);
	draw_player_marker(game);
	draw_minimap_border(game);
	return (0);
}
