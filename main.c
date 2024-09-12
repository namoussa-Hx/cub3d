/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:45:39 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/10 23:56:30 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_free	*g_free;

void	init_data(t_data *data)
{
	data->maze.map = NULL;
	data->maze.no = NULL;
	data->maze.so = NULL;
	data->maze.we = NULL;
	data->maze.ea = NULL;
	data->maze.f = 0;
	data->maze.c = 0;
	data->maze.height = 0;
	data->player.angle = 0;
	data->player.fov = PI / 3;
	data->player.player_x = 0;
	data->player.player_y = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->x_mouse_prev = 0;
	data->hide_mouse = 0;
	data->enemy.x = 0;
	data->enemy.y = 0;
	data->enemy.enemy_index = 0;
	data->enemy.x_enemy = 0;
	data->enemy.y_enemy = 0;
	data->is_door = 0;
	data->image_door = NULL;
	data->addr_door = NULL;
	data->scale_door = NULL;
	data->width_door = 0;
	data->height_door = 0;
	data->bpp_door = 0;
	data->size_line_door = 0;
	data->distance_to_door = 0;
	data->is_door_open = 0;
	data->endian_door = 0;
	data->x_door = -1;
	data->y_door = -1;
}

int	update(t_data *game)
{
	int			x;
	int			tile_size;
	float		ray_angle;
	static int	index;
	int			width;
	int			height;

	x = 0;
	tile_size = 30;
	if (index >= SPRITE_FRAMES * 6)
		index = 0;
	width = game->walls->width_player[index / 6];
	height = game->walls->height_player[index / 6];
	memset(game->img_data, 0, WIDTH * HEIGHT * (game->bpp / 8));
	render_color(game);
	render_flor(game);
	while (x < WIDTH)
	{
		ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0
					/ tanf(game->player.fov / 2.0)));
		cast_ray_dda(game, ray_angle, x, tile_size);
		x++;
	}
	render_minimap(game);
	render1_player(game, game->walls->addr_player[index / 6], width, height);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	index++;
	return (0);
}
int	mouse_hook(int x_mouse, int y_mouse, t_data *game)
{
	(void)y_mouse;
	if (game->player.angle >= 2 * PI)
		game->player.angle -= 2 * PI;
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (x_mouse > game->x_mouse_prev)
		game->player.angle += 0.05;
	else if (x_mouse < game->x_mouse_prev)
		game->player.angle -= 0.05;
	if (game->hide_mouse == 0)
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
int	mouse_hide(t_data *game)
{
	game->hide_mouse = 0;
	mlx_mouse_hide(game->mlx, game->win);
	return (0);
}

int	ft_exit(t_data *game)
{
	destroy_all(game);
	exit(0);
	return (0);
}
int	destroy_all(t_data *game)
{
	int i;

	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img);
	while(i < 6)
	{
		mlx_destroy_image(game->mlx, game->walls->images[i]);
		i++;
	}
	i = 0;
	while(i < 37)
	{
		mlx_destroy_image(game->mlx, game->walls->player[i]);
		i++;
	}
	free_all(&g_free);
	exit(0);
	return (0);
}

int	free_parse(void)
{
	free_all(&g_free);
	exit(0);
	return (0);
}
int	main(int ac, char **av)
{
	t_data	data;
	int		tile_size;

	if (ac == 2)
	{
		g_free = NULL;
		init_data(&data);
		if (parse_cub(av[1], &data) && print_error("Error\n") && free_parse())
			return (1);
		data.walls = malloc(sizeof(t_images));
		addback(&g_free, newnode(data.walls));
		ft_bzero(data.walls, sizeof(t_images));
		data.textures = malloc(sizeof(t_textures));
		addback(&g_free, newnode(data.textures));
		ft_bzero(data.textures, sizeof(t_textures));
		tile_size = 30;
		data.player.player_x = (data.player.x * tile_size) + (tile_size / 2);
		data.player.player_y = (data.player.y * tile_size) + (tile_size / 2);
		data.x_mouse_prev = WIDTH / 2;
		init_walls(&data);
		init_player(&data);
		data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
		data.img_data = mlx_get_data_addr(data.img, &data.bpp, &data.size_line,
				&data.endian);
		update(&data);
		mlx_hook(data.win, 02, 1L << 0, key_hook, &data);
		mlx_hook(data.win, 6, 1L << 6, mouse_hook, &data);
		mlx_hook(data.win, 7, 1L << 4, mouse_hide, &data);
		mlx_hook(data.win, 17, 0, ft_exit, &data);
		mlx_mouse_hide(data.mlx, data.win);
		mlx_loop_hook(data.mlx, update, &data);
		mlx_loop(data.mlx);
		destroy_all(&data);
		mlx_mouse_show(data.mlx, data.win);
	}
	else
		print_error("Error: invalid number of arguments\n");
	return (0);
}
