#include "../cub3d.h"


// void render_minimap(t_data *game, int tile_size, int player_x, int player_y) 
// {

//     int x, y;
//     int color;
//      int height = game->maze.height;
//      int width = game->maze.width;
//     int map_x;
//     int map_y;
//     game->mini_map.img = mlx_new_image(game->mlx, width * tile_size, height * tile_size);
//     game->mini_map.img_data = mlx_get_data_addr(game->mini_map.img, 
//     &game->mini_map.bpp, &game->mini_map.size_line, &game->mini_map.endian);

 
//     mlx_put_image_to_window(game->mlx, game->win, game->mini_map.img, 0, 0);
//     // mlx_destroy_image(game->mlx, game->mini_map.img);
  
// }

void render_3d_projection(t_data *game, float distance, int ray_index, int tile_size)
{
    int texture_y;
    int wall_height;
    int draw_start;
    int draw_end;
    int texture_index;
    int *texture_buffer;
    int color;
    int y;
    float step;
    float texture_pos;
    int pixel_index;
    int texture_width;
    int texture_x;
    float wall_x;
    if (distance <= 0) distance = 0.1;
     wall_height = (int)(tile_size * HEIGHT / distance);
     draw_start = HEIGHT / 2 - wall_height / 2 ;
    if (draw_start < 0) draw_start = 0;
     draw_end = wall_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

    if (game->vector.side == 0)
        wall_x = game->player.player_y / tile_size + distance * game->vector.ray_dir_y / tile_size; //vertical (side == 0) wla horizontal (side == 1) 
    else
        wall_x = game->player.player_x / tile_size + distance * game->vector.ray_dir_x / tile_size;
    wall_x -= floor(wall_x);

    if (game->vector.side == 0)
    {

        if(game->vector.ray_dir_x > 0)
             texture_index = 0;
        else
            texture_index = 1; // east wla west
    } 
    else
    {
         if(game->vector.ray_dir_y > 0) 
            texture_index = 2;
        else
            texture_index =  3; // north wla south
    }
    texture_buffer = game->textures->scale[texture_index];
    texture_width = game->textures->width;
    texture_x = (int)(wall_x * (float)texture_width);
    if ((game->vector.side == 0 && game->vector.ray_dir_x > 0) ||
        (game->vector.side == 1 && game->vector.ray_dir_y < 0))
        texture_x = texture_width - texture_x - 1;
    step = 1.0 * game->textures->height / wall_height;//hna fin kanscaliw
    texture_pos = (draw_start - HEIGHT / 2 + wall_height / 2) * step;
    y = draw_start;
    while(y < draw_end)
    {
         texture_y = (int)texture_pos % (game->textures->height - 1); 
        texture_pos += step; //kanzid position ila derna liha & m3a texture height tatb9a nefs color 3la 7sab tol dyal texture 

        color = texture_buffer[texture_y * texture_width + texture_x]; //mli tandir scaling tanb9a nto7o fnafs color hadchi bach tansciliw 7it tandir & opertion 3la hsab tol d texture
        
        if (game->vector.side == 1)
            color = (color >> 1) & 8355711; //hna 4ir kanraj3om dark

         pixel_index = (y * WIDTH + ray_index) * (game->bpp / 8);
        *((unsigned int *)(game->img_data + pixel_index)) = color;
        y++;
    }
}

void render_color(t_data *game) 
{
    int draw_end;
    int y;
    int x;
    int pixel_index;

    draw_end = HEIGHT / 2;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
    y = 0;
    while( y < draw_end) 
    {
        x = 0;
         while(x < WIDTH)
         {

        pixel_index = (y * WIDTH + x) * (game->bpp / 8);
         *((unsigned int *)(game->img_data + pixel_index)) = game->maze.c;
         x++;
         }
    y++;
    }
}

void render_flor(t_data *game) 
{
    int draw_end;
    int y;
    int x;
    int pixel_index;

    draw_end = HEIGHT ;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
    y =  HEIGHT / 2;
    while( y < draw_end) 
    {
        x = 0;
         while(x < WIDTH)
         {

        pixel_index = (y * WIDTH + x) * (game->bpp / 8);
         *((unsigned int *)(game->img_data + pixel_index)) = game->maze.f;
         x++;
         }
    y++;
    }
}
void cast_ray_dda(t_data *game, float angle, int ray_index, int tile_size) 
{
    game->vector.map_x = (int)(game->player.player_x / tile_size);
    game->vector.map_y = (int)(game->player.player_y / tile_size);
    game->vector.ray_dir_x = cosf(angle);
    game->vector.ray_dir_y = sinf(angle);

// int x_mousse;
// int y_mousse;   

//    mlx_mouse_get_pos(game->win, &x_mousse, &y_mousse);


    game->vector.delta_dist_x = fabs(1 / game->vector.ray_dir_x);
    game->vector.delta_dist_y = fabs(1 / game->vector.ray_dir_y);
    game->vector.hit = 0;

    if (game->vector.ray_dir_x < 0) 
    {
        game->vector.step_x = -1;
        game->vector.side_dist_x = (game->player.player_x / tile_size - game->vector.map_x) * game->vector.delta_dist_x;
    } 
    else 
    {
        game->vector.step_x = 1;
        game->vector.side_dist_x = (game->vector.map_x + 1.0 - game->player.player_x / tile_size) * game->vector.delta_dist_x;
    }

    if (game->vector.ray_dir_y < 0) 
    {
        game->vector.step_y = -1;
        game->vector.side_dist_y = (game->player.player_y / tile_size - game->vector.map_y) * game->vector.delta_dist_y;
    }
    else 
    {
        game->vector.step_y = 1;
        game->vector.side_dist_y = (game->vector.map_y + 1.0 - game->player.player_y / tile_size) * game->vector.delta_dist_y;
    }

    while (game->vector.hit == 0) 
    {
        if (game->vector.side_dist_x < game->vector.side_dist_y) 
        {
            game->vector.side_dist_x += game->vector.delta_dist_x;
            game->vector.map_x += game->vector.step_x;
            game->vector.side = 0;
        } 
        else
        {
            game->vector.side_dist_y += game->vector.delta_dist_y;
            game->vector.map_y += game->vector.step_y;
            game->vector.side = 1;
        }

        if (game->vector.map_y < 0 || game->vector.map_y >= game->maze.height ||
            game->vector.map_x < 0 || game->vector.map_x >= game->maze.width)
            return; // Out of bounds, stop processing

        if (game->maze.map[game->vector.map_y][game->vector.map_x] == '1')
            game->vector.hit = 1;
    }

    if (game->vector.side == 0)
    {
        game->vector.perp_wall_dist = (game->vector.map_x - game->player.player_x / tile_size + (1 - game->vector.step_x) / 2) / game->vector.ray_dir_x;
    } 
    else 
    {
        game->vector.perp_wall_dist = (game->vector.map_y - game->player.player_y / tile_size + (1 - game->vector.step_y) / 2) / game->vector.ray_dir_y;
    }

    render_3d_projection(game, game->vector.perp_wall_dist * tile_size, ray_index, tile_size);
}

int key_hook(int keycode, t_data *game) 
{
    int tile_size;
    int map_x;
    int map_y;
    tile_size = 30;
    if (keycode == 65361)
   game->player.angle -= rot_speed;
    if (keycode == 65363) 
        game->player.angle += rot_speed;
 
    if (keycode == 65362) 
    {
        map_x = (int)((game->player.player_x + cosf(game->player.angle) * move_speed) / tile_size);
        map_y = (int)((game->player.player_y + sinf(game->player.angle) * move_speed) / tile_size);
        if (game->maze.map[map_y][map_x] != '1') 
        {
            game->player.player_x += cosf(game->player.angle) * move_speed;
            game->player.player_y += sinf(game->player.angle) * move_speed;
        }
    //   else 
    //      {
    //          if (game->player.angle >= 2 * PI)
    //                 game->player.angle -= 2 * PI;
    //          if (game->player.angle < 0)
    //                 game->player.angle += 2 * PI;
    //         printf("angle %f\n", game->player.angle);
    //         if (game->player.angle > 0 && game->player.angle <= PI / 2)
    //         {
    //             printf("111angle %f\n", game->player.angle);
    //             game->player.angle -= 0.09;
    //         }
    //         else if (game->player.angle > PI / 2 && game->player.angle <= PI)
    //         {
    //             printf("222angle %f\n", game->player.angle);
    //             game->player.angle += 0.09;
    //         }
    //         else if (game->player.angle > PI && game->player.angle <= 3 * PI / 2)
    //         {
    //             printf("333angle %f\n", game->player.angle);
    //             game->player.angle -= 0.09;
    //         }
    //         else if (game->player.angle > 3 * PI / 2 && game->player.angle <= 2 * PI)
    //         {
    //             printf("444angle %f\n", game->player.angle);
    //             game->player.angle += 0.09;
    //         }
    //  }
    }
    if (keycode == 65364)
    {
        map_x = (int)((game->player.player_x - cosf(game->player.angle) * move_speed) / tile_size);
        map_y = (int)((game->player.player_y - sinf(game->player.angle) * move_speed) / tile_size);
        if (game->maze.map[map_y][map_x] != '1') 
        {
            game->player.player_x -= cosf(game->player.angle) * move_speed;
            game->player.player_y -= sinf(game->player.angle) * move_speed;
        }
    }
    if (keycode == 65307) 
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    
    return (0);
}
