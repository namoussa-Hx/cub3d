/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:59:39 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/14 18:00:19 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	border_init(t_minimap *mini)
{
	mini->center_x = WIDTH - MINIMAP_RADIUS - 10;
	mini->center_y = MINIMAP_RADIUS;
	mini->y = -MINIMAP_RADIUS;
}

int	is_inside_circle(int x, int y, int rad)
{
	int	dx;
	int	dy;

	dx = x - MINIMAP_RADIUS;
	dy = y - MINIMAP_RADIUS;
	return ((dx * dx + dy * dy) <= (rad * rad));
}

void	check_border(t_minimap *mini, t_data *game)
{
	if (abs(mini->x * mini->x + mini->y * mini->y - MINIMAP_RADIUS
			* MINIMAP_RADIUS) < MINIMAP_RADIUS)
	{
		mini->screen_x = mini->center_x + mini->x;
		mini->screen_y = mini->center_y + mini->y;
		mini->pixel_index = (mini->screen_y * game->size_line) + (mini->screen_x
				* (game->bpp / 8));
		*((unsigned int *)(game->img_data + mini->pixel_index)) = 0xFFFFFF;
	}
}