/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:06:41 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/14 16:28:29 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_init(t_render *render, t_data *game, double distance)
{
	if (distance <= 0)
		distance = 0.1;
	render->wall_height = (int)(30 * HEIGHT / distance);
	render->draw_start = HEIGHT / 2 - render->wall_height / 2;
	if (render->draw_start < 0)
		render->draw_start = 0;
	render->draw_end = render->wall_height / 2 + HEIGHT / 2;
	if (render->draw_end >= HEIGHT)
		render->draw_end = HEIGHT - 1;
	if (game->vector.side == 0)
		render->wall_x = (game->player.player_y / 30) + distance
			* (game->vector.ray_dir_y / 30);
	else
		render->wall_x = (game->player.player_x / 30) + distance
			* (game->vector.ray_dir_x / 30);
	render->wall_x -= floor(render->wall_x);
}

void	render_check(t_data *game, t_render *render)
{
	if (game->vector.side == 0)
	{
		if (game->vector.ray_dir_x > 0)
			render->texture_index = 0;
		else
			render->texture_index = 1;
	}
	else
	{
		if (game->vector.ray_dir_y > 0)
			render->texture_index = 2;
		else
			render->texture_index = 3;
	}
	if (game->is_door)
	{
		if (game->is_door_open == 2)
			render->texture_index = 5;
		else
			render->texture_index = 4;
	}
	render->texture_x = (int)(render->wall_x * (float)render->texture_width);
	render->texture_buffer = game->walls->scale[render->texture_index];
	render->texture_width = game->walls->width[render->texture_index];
}

void	init_ren(t_render *render)
{
	render->texture_y = 0;
	render->wall_height = 0;
	render->draw_start = 0;
	render->draw_end = 0;
	render->texture_index = 0;
	render->texture_buffer = 0;
	render->color = 0;
	render->y = 0;
	render->step = 0;
	render->texture_pos = 0;
	render->pixel_index = 0;
	render->texture_width = 0;
	render->texture_x = 0;
	render->wall_x = 0;
}

void	render_con(t_render *render, t_data *game)
{
	render->texture_x = (int)(render->wall_x * (float)render->texture_width);
	if ((game->vector.side == 0 && game->vector.ray_dir_x > 0)
		|| (game->vector.side == 1 && game->vector.ray_dir_y < 0))
		render->texture_x = render->texture_width - render->texture_x - 1;
	render->step = 1.0 * game->walls->height[render->texture_index]
		/ render->wall_height;
	render->texture_pos = (render->draw_start - HEIGHT / 2 + render->wall_height
			/ 2) * render->step;
	render->y = render->draw_start;
}

void	render_3d_projection(t_data *game, float distance, int ray_index)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	init_ren(render);
	if (distance <= 0)
		distance = 0.1;
	render_init(render, game, distance);
	render_check(game, render);
	render_con(render, game);
	while (render->y < render->draw_end)
	{
		render->texture_y = (int)render->texture_pos
			% (game->walls->height[render->texture_index] - 1);
		render->texture_pos += render->step;
		render->color = render->texture_buffer[render->texture_y
			* render->texture_width + render->texture_x];
		if (game->vector.side == 1)
			render->color = (render->color >> 1) & 8355711;
		render->pixel_index = (render->y * WIDTH + ray_index) * (game->bpp / 8);
		*((unsigned int *)(game->img_data
					+ render->pixel_index)) = render->color;
		render->y++;
	}
	game->is_door_open = 0;
	return (game->is_door = 0, (void)free(render));
}
