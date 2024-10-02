/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:52:51 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:14:37 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	_f_c(char *str)
{
	if ((str[0] == 'C' || str[0] == 'F')
		&& (str[1] != ' ' && str[1] != '\t'))
		return (1);
	return (0);
}

void	init_buffer(t_data *game)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	*buffer;

	i = -1;
	while ((++i) < 6)
	{
		buffer = (int *)ft_malloc(sizeof(int) * game->walls->width[i]
				* game->walls->height[i]);
		j = -1;
		while ((++j) < game->walls->height[i])
		{
			k = -1;
			while ((++k) < game->walls->width[i])
			{
				l = game->walls->width[i] * j + k;
				buffer[game->walls->width[i] * j + k] = game->walls->addr[i][l];
			}
		}
		game->walls->scale[i] = buffer;
	}
}

void	walls_address(t_data *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		game->walls->addr[i] = (int *)mlx_get_data_addr(game->walls->images[i],
				&game->walls->bpp[i], &game->walls->size_line[i],
				&game->walls->endian[i]);
		i++;
	}
	init_buffer(game);
}

void	*file_to_img(t_data *data, char *img_path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, img_path, w, h);
	if (!img)
	{
		print_error("Error\n");
		exit(1);
	}
	return (img);
}

void	init_walls(t_data *game)
{
	game->mlx = mlx_init();
	game->walls->images[0] = file_to_img(game, game->maze.no,
			&game->walls->width[0], &game->walls->height[0]);
	game->walls->images[1] = file_to_img(game, game->maze.so,
			&game->walls->width[1], &game->walls->height[1]);
	game->walls->images[2] = file_to_img(game, game->maze.we,
			&game->walls->width[2], &game->walls->height[2]);
	game->walls->images[3] = file_to_img(game, game->maze.ea,
			&game->walls->width[3], &game->walls->height[3]);
	game->walls->images[4] = file_to_img(game, DOOR1,
			&game->walls->width[4], &game->walls->height[4]);
	game->walls->images[5] = file_to_img(game, DOOR2,
			&game->walls->width[5], &game->walls->height[5]);
	walls_address(game);
}
