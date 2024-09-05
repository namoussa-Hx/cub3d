#include "cub3d.h"

void	init_buffer(t_data *game)
{
    int		i;
	int		j;
	int		k;
	int		l;
	int		*buffer;

	i = 0;
	while (i < 4)
	{
		buffer = (int *)malloc(sizeof(int) * game->textures->width * game->textures->height);
		j = 0;
		while (j < game->textures->height )
		{
			k = 0;
			while (k < game->textures->width)
			{
				l = game->textures->width * j + k;
				buffer[game->textures->width * j + k] = game->textures->addr[i][l];
				k++;
			}
			j++;
		}
		game->textures->scale[i] = buffer;
		i++;
	}
	mlx_destroy_image(game->mlx, game->textures->images[0]);
	mlx_destroy_image(game->mlx, game->textures->images[1]);
	mlx_destroy_image(game->mlx, game->textures->images[2]);
	mlx_destroy_image(game->mlx, game->textures->images[3]);
}

void scale_texture(int *source, int *dest, int src_width, int src_height, int dest_width, int dest_height) 
{
    float x_ratio = (float)src_width / dest_width;
    float y_ratio = (float)src_height / dest_height;
    float px, py;
    int x, y, sx, sy;
	y = 0;
    while(y < dest_height)
	{
		x = 0;
        while(x < dest_width) 
		{
            px = x * x_ratio;
            py = y * y_ratio;
            sx = (int)px;
            sy = (int)py;
            dest[y * dest_width + x] = source[sy * src_width + sx];
        }
    }
}

    

void	texture_address(t_data *game)
{

	game->textures->addr[0] = (int *)mlx_get_data_addr(game->textures->images[0], 
	&game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	game->textures->addr[1] = (int *)mlx_get_data_addr(game->textures->images[1], 
	&game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	game->textures->addr[2] = (int *)mlx_get_data_addr(game->textures->images[2], 
	&game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	game->textures->addr[3] = (int *)mlx_get_data_addr(game->textures->images[3], 
	&game->textures->bpp, &game->textures->size_line, &game->textures->endian);
	// if(!game->textures->addr[0] || !game->textures->addr[1] || !game->textures->addr[2] || !game->textures->addr[3])
	// {
	// 	write(2,"texutre is invalid\n",20);
	// 	exit(1);
	// }
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

void	init_textures(t_data *game)
{
	game->textures->images[0] = file_to_img(game, game->maze.no, &game->textures->width, &game->textures->height);
	game->textures->images[1] = file_to_img(game, game->maze.so, &game->textures->width, &game->textures->height);
	game->textures->images[2] = file_to_img(game, game->maze.we, &game->textures->width, &game->textures->height);
	game->textures->images[3] = file_to_img(game, game->maze.ea, &game->textures->width, &game->textures->height);
	
	// if(!game->textures->images[0] || !game->textures->images[1] || !game->textures->images[2] || !game->textures->images[3])
	// {
	// 	write(2,"texutre is invalid\n",20);
	// 	exit(1);
	// }
	texture_address(game);
}
