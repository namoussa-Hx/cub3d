
#include "cub3d.h"

void	init_plyare(t_data *game)
{
game->walls->player = malloc(SPRITE_FRAMES * sizeof(void *));
game->walls->addr_player = malloc(SPRITE_FRAMES * sizeof(int *));
game->walls->width_player = malloc(SPRITE_FRAMES * sizeof(int));
game->walls->height_player = malloc(SPRITE_FRAMES * sizeof(int));
game->walls->bpp_player = malloc(SPRITE_FRAMES * sizeof(int));
game->walls->size_line_player = malloc(SPRITE_FRAMES * sizeof(int));
game->walls->endian_player = malloc(SPRITE_FRAMES * sizeof(int));

	char *s[SPRITE_FRAMES] = {
		"textures/player/1.xpm",
		"textures/player/2.xpm",
		"textures/player/3.xpm",
		"textures/player/4.xpm",
		"textures/player/5.xpm",
		"textures/player/6.xpm",
		"textures/player/7.xpm",
		"textures/player/8.xpm",
		"textures/player/9.xpm",
		"textures/player/10.xpm",
		"textures/player/11.xpm",
		"textures/player/12.xpm",
		"textures/player/13.xpm",
		"textures/player/14.xpm",
		"textures/player/15.xpm",
		"textures/player/16.xpm",
		"textures/player/17.xpm",
		"textures/player/18.xpm",
		"textures/player/19.xpm",
		"textures/player/20.xpm",
		"textures/player/21.xpm",
		"textures/player/22.xpm",
		"textures/player/23.xpm",
		"textures/player/24.xpm",
		"textures/player/25.xpm",
		"textures/player/26.xpm",
		"textures/player/27.xpm",
		"textures/player/28.xpm",
		"textures/player/29.xpm",
		"textures/player/30.xpm",
		"textures/player/31.xpm",
		"textures/player/32.xpm",
		"textures/player/33.xpm",
		"textures/player/34.xpm",
		"textures/player/35.xpm",
		"textures/player/36.xpm",
		"textures/player/37.xpm",
		"textures/player/38.xpm",
		"textures/player/39.xpm",
		"textures/player/40.xpm"
	};
	for (int i = 0; i < 40; i++)
	{
		game->walls->player[i] = mlx_xpm_file_to_image(game->mlx, s[i], &game->walls->width_player[i], &game->walls->height_player[i]);
		if (!game->walls->player[i])
			{
				print_error("Error\nPlayer texture not found");
				exit(1);
			}
		game->walls->addr_player[i] = (int *)mlx_get_data_addr(game->walls->player[i], &game->walls->bpp_player[i], &game->walls->size_line_player[i], &game->walls->endian_player[i]);
//    printf("Player texture %d :%p loaded\n",i,  game->walls->addr_player[i]);
	}
}
