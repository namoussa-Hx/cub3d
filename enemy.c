#include "cub3d.h"

void render_enemy(t_data *game)
{
    int x, y;
    int screen_x, screen_y;
    int pixel_index;
    int enemy_width = game->textures->width[game->enemy.enemy_index];
    int enemy_height = game->textures->height[game->enemy.enemy_index];
    screen_x = (int)(game->enemy.x - game->player.player_x) / TILE_SIZE + WIDTH / 2;
    screen_y = (int)(game->enemy.y - game->player.player_y) / TILE_SIZE + HEIGHT / 2;

   
    float distance = sqrtf((game->enemy.x - game->player.player_x) * (game->enemy.x - game->player.player_x) +
                           (game->enemy.y - game->player.player_y) * (game->enemy.y - game->player.player_y));
    int enemy_height_on_screen = (int)(enemy_height * HEIGHT / distance);
    int draw_start = HEIGHT / 2 - enemy_height_on_screen / 2;
    int draw_end = HEIGHT / 2 + enemy_height_on_screen / 2;

    
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

   
    for (y = draw_start; y < draw_end; y++) 
    {
        int texture_y = (int)((y - draw_start) * (float)enemy_height / enemy_height_on_screen);
        if (texture_y >= 0 && texture_y < enemy_height) 
        {
            for (x = screen_x; x < screen_x + enemy_width; x++) 
            {
                if (x >= 0 && x < WIDTH) 
                {
                    pixel_index = (y * WIDTH + x) * (game->bpp / 8);
                    *((unsigned int *)(game->img_data + pixel_index)) = 
                     game->textures->addr[game->enemy.enemy_index][texture_y * enemy_width + (x - screen_x)];
                }
            }
        }
    }
}

