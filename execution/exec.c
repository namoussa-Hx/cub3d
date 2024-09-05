#include "../cub3d.h"

// void render_3d_projection(t_data *game, float distance, int ray_index, int tile_size) 
// {
//     int wall_height;
//     int draw_start;
//     int draw_end;
//     int y;
//     int color;
//     color = 0xFF0000;
//     int pixel_index;

//     if (distance <= 0) distance = 0.1;
//     wall_height = (int)(tile_size * HEIGHT / distance);
//     draw_start = -wall_height / 2 + HEIGHT / 2;
//     if (draw_start < 0) draw_start = 0;
//     draw_end = wall_height / 2 + HEIGHT / 2;
//     if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
//     y = draw_start;
//     while( y < draw_end) 
//     {
//         pixel_index = (y * WIDTH + ray_index) * (game->bpp / 8);
//         *((unsigned int *)(game->img_data + pixel_index)) = color;
//     y++;
//     }
// }
// void render_3d_projection(t_data *game, float distance, int ray_index, int tile_size)
// {
//     int wall_height;
//     int draw_start;
//     int draw_end;
//     int y;
//     int texture_x;
//     int color;
//     int texture_index;
//     int *texture_buffer;

//     if (distance <= 0) distance = 0.1;
//     wall_height = (int)(tile_size * HEIGHT / distance);
//     draw_start = -wall_height / 2 + HEIGHT / 2;
//     if (draw_start < 0) draw_start = 0;
//     draw_end = wall_height / 2 + HEIGHT / 2;
//     if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

//     // Choose texture based on side
//     texture_index = (game->vector.side == 0) ? 0 : 1; // Update as needed
//     texture_buffer = game->textures->scale[texture_index];
//     int texture_width = game->textures->width; // Adjust if necessary

//     for (y = draw_start; y < draw_end; y++)
//     {
//         // Calculate texture coordinates
//         int texture_height = game->textures->height;
//         int texture_y = (y - draw_start) * texture_height / (draw_end - draw_start);
//         texture_x = ray_index % texture_width;

//         color = texture_buffer[texture_y * texture_width + texture_x];
//         int pixel_index = (y * WIDTH + ray_index) * (game->bpp / 8);
//         *((unsigned int *)(game->img_data + pixel_index)) = color;
//     }
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
    step = 1.0 * game->textures->height / wall_height;
    texture_pos = (draw_start - HEIGHT / 2 + wall_height / 2) * step;
    y = draw_start;
    while(y < draw_end)
    {
         texture_y = (int)texture_pos & (game->textures->height - 1); //hna fin kanscaliw
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

    if (game->vector.ray_dir_y < 0) {
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

    if (game->vector.side == 0) {
        game->vector.perp_wall_dist = (game->vector.map_x - game->player.player_x / tile_size + (1 - game->vector.step_x) / 2) / game->vector.ray_dir_x;
    } else {
        game->vector.perp_wall_dist = (game->vector.map_y - game->player.player_y / tile_size + (1 - game->vector.step_y) / 2) / game->vector.ray_dir_y;
    }

    render_3d_projection(game, game->vector.perp_wall_dist * tile_size, ray_index, tile_size);
}



int key_hook(int keycode, t_data *game) 
{
    int tile_size;
    int map_x;
    int map_y;
    int x;
    float ray_angle;

    x = 0;
    // tile_size = fmin(WIDTH / 2, HEIGHT / 2);
    tile_size = 30;
    update(game);

    if (keycode == 65361) 
        game->player.angle -= game->rot_speed;
    if (keycode == 65363) 
        game->player.angle += game->rot_speed;
    if (keycode == 65362) 
    {
        map_x = (int)((game->player.player_x + cosf(game->player.angle) * game->move_speed) / tile_size);
        map_y = (int)((game->player.player_y + sinf(game->player.angle) * game->move_speed) / tile_size);
        if (game->maze.map[map_y][map_x] != '1') 
        {
            game->player.player_x += cosf(game->player.angle) * game->move_speed;
            game->player.player_y += sinf(game->player.angle) * game->move_speed;
        // game->maze.map[game->player.x][game->player.y] = '0';
        }
    }
    if (keycode == 65364)
    {
        map_x = (int)((game->player.player_x - cosf(game->player.angle) * game->move_speed) / tile_size);
        map_y = (int)((game->player.player_y - sinf(game->player.angle) * game->move_speed) / tile_size);
        if (game->maze.map[map_y][map_x] != '1') 
        {
            game->player.player_x -= cosf(game->player.angle) * game->move_speed;
            game->player.player_y -= sinf(game->player.angle) * game->move_speed;
            // game->maze.map[game->player.x][game->player.y] = '0';
        }
    }
    if (keycode == 65307) 
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }

    memset(game->img_data, 0, WIDTH * HEIGHT * (game->bpp / 8));

    render_color(game);
    render_flor(game);
    while (x < WIDTH) 
    {
        ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0 / tanf(game->player.fov / 2.0)));
        cast_ray_dda(game, ray_angle, x, tile_size);
        x++;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}
