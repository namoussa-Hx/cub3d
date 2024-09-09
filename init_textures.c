
#include "cub3d.h"

void	buffer_enemy(t_data *game)
{
    int		i;
	int		j;
	int		k;
	int		l;
	int		*buffer;

	i = 0;
	while (i < 16)
	{
		buffer = (int *)malloc(sizeof(int) * game->textures->width[i] * game->textures->height[i]);
		j = 0;
		while (j < game->textures->height[i] )
		{
			k = 0;
			while (k < game->textures->width[i])
			{
				l = game->textures->width[i] * j + k;
				buffer[game->textures->width[i] * j + k] = game->textures->addr[i][l];
				k++;
			}
			j++;
		}
		game->textures->scale_enemy[i] = buffer;
		i++;
	}
	i = 0;
    while (i < 16)
    {
        mlx_destroy_image(game->mlx, game->textures->images[i]);
		i++;
    }
}

void textures_address(t_data *game)
{
	game->textures->addr[0] = (int *)mlx_get_data_addr(game->textures->images[0], 
	&game->textures->bpp[0], &game->textures->size_line[0], &game->textures->endian[0]);
	game->textures->addr[1] = (int *)mlx_get_data_addr(game->textures->images[1],
	&game->textures->bpp[1], &game->textures->size_line[1], &game->textures->endian[1]);
	game->textures->addr[2] = (int *)mlx_get_data_addr(game->textures->images[2],
	&game->textures->bpp[2], &game->textures->size_line[2], &game->textures->endian[2]);
	game->textures->addr[3] = (int *)mlx_get_data_addr(game->textures->images[3],
	&game->textures->bpp[3], &game->textures->size_line[3], &game->textures->endian[3]);
	game->textures->addr[4] = (int *)mlx_get_data_addr(game->textures->images[4],
	&game->textures->bpp[4], &game->textures->size_line[4], &game->textures->endian[4]);
	game->textures->addr[5] = (int *)mlx_get_data_addr(game->textures->images[5],
	&game->textures->bpp[5], &game->textures->size_line[5], &game->textures->endian[5]);
	game->textures->addr[6] = (int *)mlx_get_data_addr(game->textures->images[6],
	&game->textures->bpp[6], &game->textures->size_line[6], &game->textures->endian[6]);
	game->textures->addr[7] = (int *)mlx_get_data_addr(game->textures->images[7],
	&game->textures->bpp[7], &game->textures->size_line[7], &game->textures->endian[7]);
	game->textures->addr[8] = (int *)mlx_get_data_addr(game->textures->images[8],
	&game->textures->bpp[8], &game->textures->size_line[8], &game->textures->endian[8]);
	game->textures->addr[9] = (int *)(mlx_get_data_addr(game->textures->images[9],
	&game->textures->bpp[9], &game->textures->size_line[9], &game->textures->endian[9]));
	game->textures->addr[10] = (int *)(mlx_get_data_addr(game->textures->images[10],
	&game->textures->bpp[10], &game->textures->size_line[10], &game->textures->endian[10]));
	game->textures->addr[11] = (int *)(mlx_get_data_addr(game->textures->images[11],
	&game->textures->bpp[11], &game->textures->size_line[11], &game->textures->endian[11]));
	game->textures->addr[12] = (int *)(mlx_get_data_addr(game->textures->images[12],
	&game->textures->bpp[12], &game->textures->size_line[12], &game->textures->endian[12]));
	game->textures->addr[13] = (int *)(mlx_get_data_addr(game->textures->images[13],
	&game->textures->bpp[13], &game->textures->size_line[13], &game->textures->endian[13]));
	game->textures->addr[14] = (int *)(mlx_get_data_addr(game->textures->images[14],
	&game->textures->bpp[14], &game->textures->size_line[14], &game->textures->endian[14]));
	game->textures->addr[15] = (int *)(mlx_get_data_addr(game->textures->images[15],
		&game->textures->bpp[15], &game->textures->size_line[15], &game->textures->endian[15]));
   buffer_enemy(game);
}


void init_textures(t_data *game)
{
	game->textures->images[0] = file_to_img(game, ENEMY0, 
	&game->textures->width[0], &game->textures->height[0]);
	game->textures->images[1] = file_to_img(game, ENEMY1,
	&game->textures->width[1], &game->textures->height[1]);
	game->textures->images[2] = file_to_img(game, ENEMY2,
	&game->textures->width[2], &game->textures->height[2]);
	game->textures->images[3] = file_to_img(game, ENEMY3,
	&game->textures->width[3], &game->textures->height[3]);
	game->textures->images[4] = file_to_img(game, ENEMY4,
	&game->textures->width[4], &game->textures->height[4]);
	game->textures->images[5] = file_to_img(game, ENEMY5,
	&game->textures->width[5], &game->textures->height[5]);
	game->textures->images[6] = file_to_img(game, ENEMY6,
	&game->textures->width[6], &game->textures->height[6]);
	game->textures->images[7] = file_to_img(game, ENEMY7,
	&game->textures->width[7], &game->textures->height[7]);
	game->textures->images[8] = file_to_img(game, ENEMY8,
	&game->textures->width[8], &game->textures->height[8]);
	game->textures->images[9] = file_to_img(game, ENEMY9,
	&game->textures->width[9], &game->textures->height[9]);
	game->textures->images[10] = file_to_img(game, ENEMY10,
	&game->textures->width[10], &game->textures->height[10]);
	game->textures->images[11] = file_to_img(game, ENEMY11,
	&game->textures->width[11], &game->textures->height[11]);
	game->textures->images[12] = file_to_img(game, ENEMY12,
	&game->textures->width[12], &game->textures->height[12]);
	game->textures->images[13] = file_to_img(game, ENEMY13,
	&game->textures->width[13], &game->textures->height[13]);
	game->textures->images[14] = file_to_img(game, ENEMY14,
	&game->textures->width[14], &game->textures->height[14]);
	game->textures->images[15] = file_to_img(game, ENEMY15,
	&game->textures->width[15], &game->textures->height[15]);
	textures_address(game);
}