#include "../cub3d.h"

void draw_map(t_data *game, int tile_size) 
{
    int x;
    int y;
    int i;

    x = 0;
    y = 0;
    while (y < game->maze.height)
    {
        x = 0;
        while (game->maze.map[y][x] != '\n') 
        {
            if (game->maze.map[y][x] == '1')
            {
                i = 0;
                while (i < tile_size) 
                {
                    int j = 0;
                    while (j < tile_size) 
                    {
                        mlx_pixel_put(game->mlx, game->win, x * tile_size + i, y * tile_size + j, 0xFFFFFF);
                        j++;
                    }
                    i++;
                }
            }
            x++;
        }
        y++;
    }
}

// void render_3d_projection(t_data *game, float distance, int ray_index, int tile_size) 
// {
//     int wall_height;
//     int draw_start;
//     int y;
//     wall_height = (int)(tile_size * HEIGHT / distance);
//     draw_start = -wall_height / 2 + HEIGHT / 2;
//     if (draw_start < 0) draw_start = 0;
//     int draw_end = wall_height / 2 + HEIGHT / 2;
//     if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

//     y = draw_start;
//     while (y < draw_end) 
//     {
//         mlx_pixel_put(game->mlx, game->win, ray_index, y, 0xFF0000);
//         y++;
//     }
// }

// void cast_ray_dda(t_data *game, float angle, int ray_index, int tile_size) 
// {
  
    
//     game->vector.map_x = (int)(game->player.player_x / tile_size);
//     game->vector.map_y= (int)(game->player.player_y / tile_size);


//     game->vector.ray_dir_x = cosf(angle);
//     game->vector.ray_dir_y= sinf(angle);

//     game->vector.delta_dist_x  = fabsf(1 / game->vector.ray_dir_x);
//    game->vector.map_y = fabsf(1 /  game->vector.ray_dir_y);
//     game->vector.hit = 0;

//     if ( game->vector.ray_dir_x < 0) 
//     {
//         game->vector.step_x = -1;
//         game->vector.side_dist_x = (game->player.player_x / tile_size - game->vector.map_x) * game->vector.delta_dist_x;
//     } else 
//     {
//         game->vector.step_x = 1;
//         game->vector.side_dist_x = (game->vector.map_x + 1.0 - game->player.player_x / tile_size) * game->vector.delta_dist_x;
//     }
//     if (game->vector.ray_dir_y < 0) 
//     {
//         game->vector.step_y = -1;
//         game->vector.side_dist_y = (game->player.player_y / tile_size - game->vector.map_y) * game->vector.delta_dist_y;
//     } 
//     else 
//     {
//        game->vector.ray_dir_x = 1;
//         game->vector.side_dist_y = (game->vector.map_y + 1.0 - game->player.player_y / tile_size) * game->vector.delta_dist_y;
//     }

//     while (game->vector.hit == 0) 
//     {
//         if (game->vector.side_dist_x < game->vector.side_dist_y) 
//         {
//             game->vector.side_dist_x += game->vector.delta_dist_x;
//             game->vector.map_x += game->vector.step_x;
//             game->vector.side = 0;
//         } else 
//         {
//             game->vector.side_dist_y += game->vector.delta_dist_y;
//             game->vector.map_y += game->vector.step_y;
//             game->vector.side = 1;
//         }
//         if (game->maze.map[game->vector.map_y][game->vector.map_x] != '0') game->vector.hit = 1;
//     }

//     if (game->vector.side == 0) game->vector.perp_wall_dist = (game->vector.map_x - game->player.player_x / tile_size + (1 - game->vector.step_x) / 2) / game->vector.ray_dir_x;
//     else           game->vector.perp_wall_dist = (game->vector.map_y - game->player.player_y / tile_size + (1 - game->vector.step_y) / 2) / game->vector.ray_dir_y;

//     render_3d_projection(game, game->vector.perp_wall_dist * tile_size, ray_index, tile_size);
// }

// void draw_player(t_data *game, int tile_size) 
// {
//     int i;
//     int j;
//     i = -2;
//     while (i <= 2)
//     {
//         j = -2;
//         while (j <= 2) 
//         {
//             mlx_pixel_put(game->mlx, game->win, game->player.player_x + i, game->player.player_y + j, 0xFFFF00);
//             j++;
//         }
//         i++;
//     }
// }

// int key_hook(int keycode, t_data *game) 
// {
//     int tile_size;
//     int map_x;
//     int map_y;
//     int x;
//     float ray_angle;
//     x = 0;
//     tile_size = fmin(WIDTH / 2, HEIGHT / 2);

//     if (keycode == 65361) //lyser
//         game->player.angle -= rotation_speed;
//     if (keycode == 65363)  // limen
//         game->player.angle += rotation_speed;
//     if (keycode == 65362) 
//     {  // lfo9
//         map_x = (int)(game->player.player_x + cosf(game->player.angle) * move_speed) / tile_size;
//         map_y = (int)(game->player.player_y+ sinf(game->player.angle) * move_speed) / tile_size;
//       //  if (game->map.data[map_y * game->map.width + map_x] != 1) 
//         if(game->maze.map[map_y][map_x] != '1')
//         {
//             game->player.player_x += cosf(game->player.angle) * move_speed;
//             game->player.player_x  += sinf(game->player.angle) * move_speed;
//         }
//     }
//     if (keycode == 65364) 
//     {  // lte7t
//         map_x = (int)(game->player.player_x - cosf(game->player.angle) * move_speed) / tile_size;
//         map_y = (int)(game->player.player_y - sinf(game->player.angle) * move_speed) / tile_size;
//         if(game->maze.map[map_y][map_x] != '1')
//         {
//             game->player.player_x -= cosf(game->player.angle) * move_speed;
//             game->player.player_x  -= sinf(game->player.angle) * move_speed;
//         }
//     }
//     if (keycode == 65307) 
//     {
//         mlx_destroy_window(game->mlx, game->win);
//         exit(0);
//     }

//     mlx_clear_window(game->mlx, game->win);
//     while (x < WIDTH) 
//     {
//         ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0 / tanf(game->player.fov / 2.0)));
//         cast_ray_dda(game, ray_angle, x, tile_size);
//         x++;
//     }

//     return (0);
// }
