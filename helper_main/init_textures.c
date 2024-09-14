/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:37:44 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/12 14:37:45 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	allocate_player(t_data *game)
{
	game->walls->player = malloc(SPRITE_FRAMES * sizeof(void *));
	addback(&g_free, newnode(game->walls->player));
	game->walls->addr_player = malloc(SPRITE_FRAMES * sizeof(int *));
	addback(&g_free, newnode(game->walls->addr_player));
	game->walls->width_player = malloc(SPRITE_FRAMES * sizeof(int));
	addback(&g_free, newnode(game->walls->width_player));
	game->walls->height_player = malloc(SPRITE_FRAMES * sizeof(int));
	addback(&g_free, newnode(game->walls->height_player));
	game->walls->bpp_player = malloc(SPRITE_FRAMES * sizeof(int));
	addback(&g_free, newnode(game->walls->bpp_player));
	game->walls->size_line_player = malloc(SPRITE_FRAMES * sizeof(int));
	addback(&g_free, newnode(game->walls->size_line_player));
	game->walls->endian_player = malloc(SPRITE_FRAMES * sizeof(int));
	addback(&g_free, newnode(game->walls->endian_player));
}

void	handle_error(t_data *game, int index)
{
	if (!game->walls->player[index])
	{
		print_error("Error\nPlayer texture not found");
		exit(1);
	}
}

void	mlx_player(t_data *game, const char *s[SPRITE_FRAMES])
{
	int	i;

	i = 0;
	while (i < 37)
	{
		game->walls->player[i] = mlx_xpm_file_to_image(game->mlx, (char *)s[i],
				&game->walls->width_player[i],
				&game->walls->height_player[i]);
		handle_error(game, i);
		game->walls->addr_player[i] = (int *)mlx_get_data_addr(
				game->walls->player[i], &game->walls->bpp_player[i],
				&game->walls->size_line_player[i],
				&game->walls->endian_player[i]);
		i++;
	}
}

void	load_textures(t_data *game)
{
	const char	*s[SPRITE_FRAMES] = {
		"textures/player/4.xpm", "textures/player/5.xpm",
		"textures/player/6.xpm", "textures/player/7.xpm",
		"textures/player/8.xpm", "textures/player/9.xpm",
		"textures/player/10.xpm", "textures/player/11.xpm",
		"textures/player/12.xpm", "textures/player/13.xpm",
		"textures/player/14.xpm", "textures/player/15.xpm",
		"textures/player/16.xpm", "textures/player/17.xpm",
		"textures/player/18.xpm", "textures/player/19.xpm",
		"textures/player/20.xpm", "textures/player/21.xpm",
		"textures/player/22.xpm", "textures/player/23.xpm",
		"textures/player/24.xpm", "textures/player/25.xpm",
		"textures/player/26.xpm", "textures/player/27.xpm",
		"textures/player/28.xpm", "textures/player/29.xpm",
		"textures/player/30.xpm", "textures/player/31.xpm",
		"textures/player/32.xpm", "textures/player/33.xpm",
		"textures/player/34.xpm", "textures/player/35.xpm",
		"textures/player/36.xpm", "textures/player/37.xpm",
		"textures/player/38.xpm", "textures/player/39.xpm",
		"textures/player/40.xpm"};

	mlx_player(game, s);
}

void	init_player(t_data *game)
{
	allocate_player(game);
	load_textures(game);
}
