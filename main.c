/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:45:39 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:36:11 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update(t_data *game)
{
	int			x;
	float		ray_angle;
	static int	index;
	int			width;
	int			height;

	x = -1;
	if (index >= SPRITE_FRAMES * 4)
		index = 0;
	width = game->walls->width_player[index / 4];
	height = game->walls->height_player[index / 4];
	memset(game->img_data, 0, WIDTH * HEIGHT * (game->bpp / 8));
	render_color(game);
	render_flor(game);
	while (++x < WIDTH)
	{
		ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0
					/ tanf(game->player.fov / 2.0)));
		cast_ray_dda(game, ray_angle, x, 30);
	}
	render_minimap(game);
	render1_player(game, game->walls->addr_player[index / 4], width, height);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	index++;
	return (0);
}

int	ft_exit(t_data *game)
{
	destroy_all(game);
	exit(0);
	return (0);
}

int	free_parse(void)
{
	free_all();
	exit(0);
	return (0);
}

void	ft_mlx(t_data *game)
{
	init_walls(game);
	init_player(game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_hook(game->win, 02, 1L << 0, key_hook, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_hook, game);
	mlx_hook(game->win, 7, 1L << 4, mouse_hide, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		init_data(&data);
		if (parse_cub(av[1], &data) && print_error("Error\n") && free_parse())
			return (1);
		data.walls = ft_malloc(sizeof(t_images));
		ft_bzero(data.walls, sizeof(t_images));
		data.textures = ft_malloc(sizeof(t_textures));
		ft_bzero(data.textures, sizeof(t_textures));
		data.player.player_x = (data.player.x * 30) + (30 / 2);
		data.player.player_y = (data.player.y * 30) + (30 / 2);
		data.x_mouse_prev = WIDTH / 2;
		ft_mlx(&data);
	}
	else
		print_error("Error: invalid number of arguments\n");
	return (0);
}
