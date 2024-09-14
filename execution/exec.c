/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:07:13 by elchakir          #+#    #+#             */
/*   Updated: 2024/09/14 18:33:40 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_render_player(t_data *game, t_player_ren *player,
		int texture_width, int texture_height)
{
	player->src_index = 0;
	player->x_start = 0;
	player->i = 0;
	player->y_start = 0;
	player->img_addr = (unsigned int *)game->img_data;
	if (player->x_start < 0)
		player->x_start = 0;
	if (player->y_start < 0)
		player->y_start = 0;
	player->x_scale = (float)(texture_width - 20) / WIDTH;
	player->y_scale = (float)(texture_height - 20) / HEIGHT;
}

void	scale(t_player_ren *player, int texture_width)
{
	player->texture_x = (int)(player->j * player->x_scale);
	player->texture_y = (int)(player->i * player->y_scale);
	player->src_index = player->texture_x + player->texture_y * texture_width;
	if (player->x_start + player->j >= 0 && player->x_start + player->j < WIDTH
		&& player->y_start + player->i >= 0 && player->y_start
		+ player->i < HEIGHT)
	{
		if (player->texture_addr[player->src_index] != 0xff000000)
		{
			player->img_addr[player->x_start + player->j + (player->y_start
					+ player->i)
				* WIDTH] = player->texture_addr[player->src_index];
		}
	}
}

void	render1_player(t_data *game, int *player, int texture_width,
		int texture_height)
{
	t_player_ren	*player1;

	player1 = malloc(sizeof(t_player_ren));
	player1->texture_addr = (unsigned int *)player;
	init_render_player(game, player1, texture_width, texture_height);
	while (player1->i < HEIGHT)
	{
		player1->j = 0;
		while (player1->j < WIDTH)
		{
			scale(player1, texture_width);
			player1->j++;
		}
		player1->i++;
	}
	free(player1);
}

void	render_color(t_data *game)
{
	int	draw_end;
	int	y;
	int	x;
	int	pixel_index;

	draw_end = HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = 0;
	while (y < draw_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_index = (y * WIDTH + x) * (game->bpp / 8);
			*((unsigned int *)(game->img_data + pixel_index)) = game->maze.c;
			x++;
		}
		y++;
	}
}

void	render_flor(t_data *game)
{
	int	draw_end;
	int	y;
	int	x;
	int	pixel_index;

	draw_end = HEIGHT;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = HEIGHT / 2;
	while (y < draw_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_index = (y * WIDTH + x) * (game->bpp / 8);
			*((unsigned int *)(game->img_data + pixel_index)) = game->maze.f;
			x++;
		}
		y++;
	}
}

