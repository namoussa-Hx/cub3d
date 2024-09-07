#include "../cub3d.h"

int is_inside_circle(int x, int y, int center_x, int center_y, int radius)
{
    int dx ;
    int dy;
    dx = x - center_x;
    dy = y - center_y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void clear_minimap_area(t_data *game) 
{
    int center_x;
    int center_y;
    int screen_x;
    int screen_y;
    int x;
    int y;
    center_x = WIDTH - MINIMAP_RADIUS - 10;
    center_y = MINIMAP_RADIUS + 10;
    y = 0;
    while (y < MINIMAP_DIAMETER)
    {
        x = 0;
        while (x < MINIMAP_DIAMETER)
        {
            if (is_inside_circle(x, y, MINIMAP_RADIUS, MINIMAP_RADIUS, MINIMAP_RADIUS)) 
            {
                screen_x = center_x - MINIMAP_RADIUS + x;
                screen_y = center_y - MINIMAP_RADIUS + y;
                int pixel_index = (screen_y * game->size_line) + (screen_x * (game->bpp / 8));
                *((unsigned int *)(game->img_data + pixel_index)) = 0x000000; // Black background
            }
            x++;
        }
        y++;
    }
}

void draw_map_tiles(t_data *game) 
{
    int center_x;
    int center_y;
    float player_x;
    float player_y;
    int x;
    int screen_x;
    int screen_y;
    int y;
    center_x = WIDTH - MINIMAP_RADIUS - 10;
    center_y = MINIMAP_RADIUS + 10;
    player_x = game->player.player_x / 30.0f;
    player_y = game->player.player_y / 30.0f;
    y = -MINIMAP_RADIUS;
    while ( y < MINIMAP_RADIUS) 
    {
        x = -MINIMAP_RADIUS;
        while ( x < MINIMAP_RADIUS) 
        {
            if (is_inside_circle(x + MINIMAP_RADIUS, y + MINIMAP_RADIUS, MINIMAP_RADIUS, MINIMAP_RADIUS, MINIMAP_RADIUS - 2))
            {
                int map_x = (int)(player_x + x / (float)TILE_SIZE);
                int map_y = (int)(player_y + y / (float)TILE_SIZE);
                
                unsigned int color;
                if (map_x >= 0 && map_x < game->maze.width && map_y >= 0 && map_y < game->maze.height) 
                {
                  if (game->maze.map[map_y][map_x] == '1') 
                            color = 0x36454F;
                 else 
                            color = 0xADD8E6;
                } 
             else 
                 color = 0x008080;
                screen_x = center_x + x;
                screen_y = center_y + y;
                int pixel_index = (screen_y * game->size_line) + (screen_x * (game->bpp / 8));
                *((unsigned int *)(game->img_data + pixel_index)) = color;
            }
            x++;
        }
        y++;
    }
}

void draw_player_marker(t_data *game) {
    int center_x;
    int center_y;
    int x;
    int y;
    center_x = WIDTH - MINIMAP_RADIUS - 10;
    center_y = MINIMAP_RADIUS + 10;
    y = -PLAYER_MARKER_SIZE;
    while(y <= PLAYER_MARKER_SIZE)
    {
        x = -PLAYER_MARKER_SIZE;
        while( x <= PLAYER_MARKER_SIZE)
        {
            if (x*x + y*y <= PLAYER_MARKER_SIZE*PLAYER_MARKER_SIZE) {
                int screen_x = center_x + x;
                int screen_y = center_y + y;
                int pixel_index = (screen_y * game->size_line) + (screen_x * (game->bpp / 8));
                *((unsigned int *)(game->img_data + pixel_index)) =  0xFFFF00; // Yellow for player
            }
            x++;
        }
        y++;
    }
}



void draw_minimap_border(t_data *game) {
    int center_x;
    int center_y;
    int y;
    int x;
    center_x = WIDTH - MINIMAP_RADIUS - 10;
    center_y = MINIMAP_RADIUS + 10;
    y = -MINIMAP_RADIUS;

    while(y <= MINIMAP_RADIUS)
    {
        x = -MINIMAP_RADIUS;
        while(x <= MINIMAP_RADIUS) 
        {
            if (abs(x*x + y*y - MINIMAP_RADIUS*MINIMAP_RADIUS) < MINIMAP_RADIUS) {
                int screen_x = center_x + x;
                int screen_y = center_y + y;
                int pixel_index = (screen_y * game->size_line) + (screen_x * (game->bpp / 8));
                *((unsigned int *)(game->img_data + pixel_index)) = 0xFFFFFF; //white
            }
            x++;
        }
        y++;
    }
}

int render_minimap(t_data *game) 
{
    clear_minimap_area(game);
    draw_map_tiles(game);
    draw_player_marker(game);
    draw_minimap_border(game);
    return 0;
}

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
    // distance = cosf(game->angel) * 
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
    texture_width = game->textures->width[texture_index];
    texture_x = (int)(wall_x * (float)texture_width);
    if ((game->vector.side == 0 && game->vector.ray_dir_x > 0) ||
        (game->vector.side == 1 && game->vector.ray_dir_y < 0))
        texture_x = texture_width - texture_x - 1;
    step = 1.0 * game->textures->height[texture_index] / wall_height;//hna fin kanscaliw
    texture_pos = (draw_start - HEIGHT / 2 + wall_height / 2) * step;
    y = draw_start;
    while(y < draw_end)
    {
         texture_y = (int)texture_pos % (game->textures->height[texture_index] - 1); 
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
    // render_minimap(game);
}

void handle_collision(t_data *game, float player_angle, float collision_angle)
{
    float angle_diff;
    angle_diff  = fmodf(collision_angle - player_angle + PI * 3, PI * 2) - PI;
    
    if (angle_diff > 0) 
        game->player.angle -= 0.02;
    else 
        game->player.angle += 0.02;
    
    game->player.angle = fmodf(game->player.angle + PI * 2, PI * 2);
}

int key_hook(int keycode, t_data *game) 
{
    int tile_size;
    int map_x;
    int map_y;
    tile_size = 30;
    if (keycode == 65361)
   game->player.angle -= ROT_SPEED;
    if (keycode == 65363) 
        game->player.angle += ROT_SPEED;
 
    if (keycode == 65362) 
    {
        map_x = (int)((game->player.player_x + cosf(game->player.angle) * MOVE_SPEED) / tile_size);
        map_y = (int)((game->player.player_y + sinf(game->player.angle) * MOVE_SPEED) / tile_size);
        if (game->maze.map[map_y][map_x] != '1') 
        {
            game->player.player_x += cosf(game->player.angle) * MOVE_SPEED;
            game->player.player_y += sinf(game->player.angle) * MOVE_SPEED;
        }
       else
        {

           float collision_angle = atan2f(map_y * tile_size + tile_size / 2 - game->player.player_y,
                                           map_x * tile_size + tile_size / 2 - game->player.player_x);
            handle_collision(game, game->player.angle, collision_angle);
        }
    }
    if (keycode == 65364)
    {
        map_x = (int)((game->player.player_x - cosf(game->player.angle) * MOVE_SPEED) / tile_size);
        map_y = (int)((game->player.player_y - sinf(game->player.angle) * MOVE_SPEED) / tile_size);
        if (game->maze.map[map_y][map_x] != '1') 
        {
            game->player.player_x -= cosf(game->player.angle) * MOVE_SPEED;
            game->player.player_y -= sinf(game->player.angle) * MOVE_SPEED;
        }
    }
    if(keycode == 32)
    {
         game->hide_mouse = 1;
        mlx_mouse_show(game->mlx, game->win);
    }
    
    if (keycode == 65307) 
    {  
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    
    return (0);
}
