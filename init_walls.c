#include "cub3d.h"

void	init_buffer(t_data *game)
{
    int		i;
	int		j;
	int		k;
	int		l;
	int		*buffer;

	i = 0;
	while (i < 7)
	{
		buffer = (int *)malloc(sizeof(int) * game->walls->width[i] * game->walls->height[i]);
		addback(&g_free, newnode(buffer));
		j = 0;
		while (j < game->walls->height[i])
		{
			k = 0;
			while (k < game->walls->width[i])
			{
				l = game->walls->width[i] * j + k;
				buffer[game->walls->width[i] * j + k] = game->walls->addr[i][l];
				k++;
			}
			j++;
		}
		game->walls->scale[i] = buffer;
		i++;
	}
}

void	walls_address(t_data *game)
{

	game->walls->addr[0] = (int *)mlx_get_data_addr(game->walls->images[0], 
	&game->walls->bpp[0], &game->walls->size_line[0], &game->walls->endian[0]);
	game->walls->addr[1] = (int *)mlx_get_data_addr(game->walls->images[1],
	&game->walls->bpp[1], &game->walls->size_line[1], &game->walls->endian[1]);
	game->walls->addr[2] = (int *)mlx_get_data_addr(game->walls->images[2],
	&game->walls->bpp[2], &game->walls->size_line[2], &game->walls->endian[2]);
	game->walls->addr[3] = (int *)mlx_get_data_addr(game->walls->images[3],
	&game->walls->bpp[3], &game->walls->size_line[3], &game->walls->endian[3]);
	game->walls->addr[4] = (int *)mlx_get_data_addr(game->walls->images[4],
	&game->walls->bpp[4], &game->walls->size_line[4], &game->walls->endian[4]);
	game->walls->addr[5] = (int *)mlx_get_data_addr(game->walls->images[5],
	&game->walls->bpp[5], &game->walls->size_line[5], &game->walls->endian[5]);
	game->walls->addr[6] = (int *)mlx_get_data_addr(game->walls->images[6],
	&game->walls->bpp[6], &game->walls->size_line[6], &game->walls->endian[6]);
	init_buffer(game);
}

void	*file_to_img(t_data *data, char *img_path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, img_path, w, h);
	if (!img)
	{
		print_error("Error\nTexture\n");
		exit(1);
	}
	return (img);
}

void	init_walls(t_data *game)
{
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
	game->walls->images[6] = file_to_img(game, PLAYER,
	&game->walls->width[6], &game->walls->height[6]);
	walls_address(game);
}

