#include "cub3d.h"

	// mlx_put_image_to_window(game->mlx, game->win, game->textures->images[2], 0, 0);
	// mlx_loop(game->mlx);
	// exit(0);
void	texture_address(t_data *game)
{

	game->textures->addr[0] = (int *)mlx_get_data_addr(game->textures->images[0], &game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	game->textures->addr[1] = (int *)mlx_get_data_addr(game->textures->images[1], &game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	game->textures->addr[2] = (int *)mlx_get_data_addr(game->textures->images[2], &game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	game->textures->addr[3] = (int *)mlx_get_data_addr(game->textures->images[3], &game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	// scaling_image(game);
}

void	*file_to_img(t_data *data, char *img_path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, img_path, w, h);
	if (!img)
		print_error("Error\nTexture\n");
	return (img);
}

void	init_textures(t_data *game)
{
	game->textures->images[0] = file_to_img(game, game->maze.no, &game->textures->width, &game->textures->height);
	game->textures->images[1] = file_to_img(game, game->maze.so, &game->textures->width, &game->textures->height);
	game->textures->images[2] = file_to_img(game, game->maze.we, &game->textures->width, &game->textures->height);
	game->textures->images[3] = file_to_img(game, game->maze.ea, &game->textures->width, &game->textures->height);
	texture_address(game);
}
